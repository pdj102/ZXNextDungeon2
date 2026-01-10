# Roguelike ECS Architecture Principles

*Target platform: ZX Spectrum Next*  
*Language: C (z88dk or SDCC toolchain)*  

---

## 1. Overview

This document defines the architecture principles for the roguelike game engine built for the Spectrum Next.  
The engine uses an **Entity-Component-System (ECS)** model optimized for 8-bit constraints, emphasizing data locality, deterministic updates, and low CPU overhead.

---

## 2. Core Concepts

### Entities

- Entities represent unique game objects (player, monsters, items, map features, etc.).
- Identified by a small integer ID (`entity_id_t`)
- Entities own no data
- Entities contain no game logic, only an ID and limited flags.
- `MAX_ENTITIES` defines the maximum number of entities
- `ENTITY_ID_INVALID` refers to an invalid entity ID

### Components

- Components own data for one aspect of an entity e.g. position, AI, health, timer, container.
- Components contain only data and simple helper functions (no logic) that only operate on the component's data
- Components never call systems
- Implemented as **arrays** for efficient access:
  - location_t location[MAX_ENTITIES];
  - health_t health[MAX_ENTITIES];

Access to components is controlled by a mask bitfield on the entity.

### Systems

- Perform logic over entities that have specific combinations of components.
- Examples:
  - system_timer() – advances entity timers.

- Gameplay systems follow the following structure
bool system_try_xxx(...)
{
    ctx_init(&c);    // Validate & gather data
    ctx_update(&c);  // Simulate & compute outcome
    ctx_apply(&c);   // Apply side
}
- Complex actions must use a context struct


## 3. ECS Update Flow

Each game tick runs a fixed update pipeline:
+----------------------+
| Timer system         |
+----------------------+
| Player system        |
+----------------------+
| AI systen            |
+----------------------+
| Render               |
+----------------------+
| Cleanup              |
+----------------------+

## 4. Entity Lifecycle

Creation:

- Entities are created using the entity_factory, for example:
  - entity_factory_create_item(ITEM_SWORD, 1);
  - entity_factory_create_monster(CREATURE_RAT);

Deferred Destruction:

- Entities are marked for destruction using entity_mark_for_destruction()
- Prevents invalidating iteration when systems are looping over entities

Cleanup:

- During the Cleanup step systems can check for FLAG_DESTROY_PENDING and perform pre-destroy logic e.g. containers release their contents
- Finally, cleanup calls entity_destroy() to remove flagged entities and recycle IDs.

A cleanup sequence is run in a fixed order:

- system_container_cleanup();
- system_ai_cleanup();
- entity_cleanup() destroys all entities marked FLAG_DESTROY_PENDING.

## 5. Component Lifecycle

Each component should provide the following functions:

- void component_init(entity_id_t e); Initialises all components to a known state
- void component_add(entity_id_t e); Adds the component to the entity
- void component_remove(entity_id_t e); Removes the component from the entity

Optionally, provide helper functions to simplify common operations

Components never directly destroy entities — they mark them for destruction.

## 6. Data Organization

All dynamic game data resides in a global struct placed at a fixed address:

  __at (0x0000) static global_state_t g;

Prefer direct array indexing (component[e]) over lookup tables or pointers.

No dynamic allocation — memory is statically partitioned at compile time.

## 7. Map and Terrain

The map is not an entity but a world system providing spatial queries:

map_is_blocked(x, y)

map_entity_at(x, y)

Entities reference their location via a Location component.

Blocking behavior (e.g. walls, creatures) is handled by flags in map cells and entity components.

## 8. Action and Intent Model

Entities never act directly; instead, they express intent.

Systems provide *try* and *action* functions.

### Try functions

*Try* functions check if an entity has the required components and validate if the action is permisable.

If permissable,

- call *action* function(s) to execute the action
- emit an event to notify other systems of the action
- return true (success)

Examples of try functions:

- `bool inventory_system_try_pickup(entity_id_t actor, entity_id_t item)`
- `bool combat_system_try_melee_attack(entity_id_t actor, entity_id_t target)`
- `bool movement_system_try_move(entity_id_t actor, int8_t dx, int8_t dy)`

### Action functions

*Action* functions assert that the entities have the correct components and execute the action.

Action functions always succeed (or abort)

Examples of action functions:

- `void movement_system_move(entity_id_t actor, int8_t dx, int8_t dy)`
- `int8_t combat_system_take_damage(entity_id_t actor, int8_t damage, damage_type_t type)`

## 9. Event System

Systems can raise game events (e.g., EVENT_DAMAGE, EVENT_PICKUP).

Events represent things that have happened, not requests.

The engine processes them immediately (no event queue) to minimise memory usage.

Example:
event_emit(EVENT_DAMAGE, source, target, val);

## 10. Turn System

The Timer Component controls turn scheduling.

When a timer reaches zero, it's `fired` flag is set.
The player and AI systems check whether the `fired` flag is set and take a turn if it is.

## 11. AI system

The AI system is state machine based.

AI States:

- AI_IDLE
- AI_CHASE
- AI_ATTACK
- AI_FLEE

The AI system processes events immediately and changes state.
State transitions are instantaneous — they do not consume turns.

AI_system_update determines if it is the monsters turn and takes a turn if it is.

## 13. Naming Conventions

| Category      | Convention       |
| ------------- | ---------------- |
| Functions     | snake_case       |
| Types         | snake_case_t     |
|Struct fields  | snake_case       |
| Macros        | UPPER_SNAKE_CASE |

| Category           | Convention                   | Example                              |
| ------------------ | ---------------------------- | ------------------------------------ |
| System function    | `system_<name>()`            | `system_ai_update()`                 |
| Component function | `<component>_add()`          | `timer_system_add_timer()`           |
| Intent function    | `<component>_try_<action>()` | `location_try_move()`                |
| Event function     | `event_<action>()`           | `event_emit()`                       |
| Global data        | `g.<subsystem>`              | `g.entity`, `g.map`                  |
| Flags              | `FLAG_<NAME>`                | `FLAG_ALIVE`, `FLAG_DESTROY_PENDING` |

## 14. Function purity

| Function type     | Rules                     |
| ----------------- | ------------------------- |
| Init              | No side effects           |
| Update            | Only validation & setup   |
| Apply             | Only mutation             |

## 15. Performance Guidelines

Use fixed sized arrays.

No use of malloc or dynamic memory allocation.

Rather than iterating all entities systems can create lists of entities for common iterations

Use 8-bit integers wherever possible.

## 15. Design Philosophy

### Entity design rules

`entity.c`

May contain / reference:

- Entity IDs
- Component masks
- Entity flags

May call / access:

- entity functions
- component add/remove helpers

Must not call / access

- system functions
- game logic

Notes & Rationale:

Manges entity lifecycle only. No gameplay logic - pure data ownership

### Design rules

| Type      | File naming | May contain / reference | May call / access | Notes & Rationale |
| ---       | ---         | ---                     | ---               | ---               |
| Components | `*_comp.c` </br> `*_comp.h` | - Raw data </br> - Simple helpers that operate on the raw data | - n/a | Components are dumb data containers. They can define small helpers to manipulate their own data only. |
| Systems | `*_system.c` </br> `*_system.h` | - Arrays of components they operate on </br> - System logic </br> - Event handling | - Components they depend upon </br> - Other systems via well defined entry points |  Systems implement behavior by processing entities with required components. They never know about “entities” beyond their component data. Ideally they should interact with other systems via events and component data but can call other systems directly where it makes sense for performance reasons |
| Game | - `*.c` - `*.h` | - Game logic and data that is not part of the ECS | - Components | Game logic implements game world rules and behaviors that are not part of the ECS e.g. map, game specific mechanics. </br>It should not interact with other systems directly. Instead it should interact with them via events and component data.|
| Core | - `*.c` - `*.h` | - Generic functions that are not game specific | - n/a | Core implements functionality that can be reused in different games e.g. mathematical functions, direction handling, graphics, input etc|

## 17. File organisation standards

/ecs  - Contains all the code related to the Entity Component System (ECS) framework.

  /components - Contains all the component definitions and their associated functions.

  /entity - Contains all the entity-related functions and structures.

  /systems - Contains all the system implementations and structures.

/core - Contains enabling modules like UI, utils, spectrum next hardware etc.

/game - Contains game specific code like global game state, map, dungeon generator etc


## 18. Memory bank standards

To create a new bank, follow these steps:

- Define the page number in `zxnext.h`
- Create a directory named /src/*/PAGEXX and put the banked code in heere
- Add functions to call the banked code in `systems_dispatch.c`
- DO NOT call banked code directly!
- Update the make file to include the /src/*/PAGEXX directory in the build process
- Manually create the corresponding /obj/PAGEXX directory

The make file will automatically assign the correct bank for each source file based on its location within the project structure.

## 19. C language best practics

- Never use int use uint8_t, int8_t, uint16_t etc
- No magic numbers
- Use `const` everywhere possible
- Validate inputs early
- Fail fast
- use util_assert() for program issues
- return false for gameplay failure
