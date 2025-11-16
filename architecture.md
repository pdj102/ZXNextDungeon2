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
- Identified by a small integer ID (`entity_id_t`).
- Entities contain no logic, only an ID and limited flags.

### Components

- Components store data for one aspect of an entity (e.g. position, AI, health, timer, container).
- Implemented as **parallel arrays** for efficient access:
  - location_t location[MAX_ENTITIES];
  - health_t health[MAX_ENTITIES];

Access to components is controlled by a mask bitfield on the entity.

### Systems

- Perform logic over entities that have specific combinations of components.
- Examples:
  - system_timer() – advances entity timers.

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

- Entities are marked for destruction using entity_mark_for_destruction() to flag entities for later removal
- Each system checks for FLAG_DESTROY_PENDING and can perform pre-destroy logic e.g. containers release their contents
- Prevents invalidating iteration when systems are looping over entities.

Cleanup:

- Cleanup calls entity_destroy() to remove flagged entities and recycle IDs.

## 5. Component Lifecycle

Each component type should provide:

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

Entities never act directly; instead, they express intent:

- creature_actions_try_pickup(entity_id_t creature, entity_id_t item)
- creature_actions_try_melee_attack(entity_id_t creature, entity_id_t target)
- movement_system_try_move(entity_id_t entity, int8_t dx, int8_t dy)

The Action System validates and resolves intents (collision, blocking, etc.).

This ensures deterministic and easily testable simulation.

## 9. Event System

Systems can raise game events (e.g., EVENT_DAMAGE, EVENT_PICKUP).

Events represent things that have happened, not requests.

The engine processes them immediately (no event queue) to minimise memory usage.

Example:
event_emit(EVENT_DAMAGE, source, target);

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

## 12. Cleanup Phase

To maintain determinism and avoid modifying collections mid-update:

Systems mark entities or components for destruction.

A cleanup sequence is run in a fixed order:
system_container_cleanup();
system_ai_cleanup();
system_combat_cleanup();
entity_cleanup();
entity_cleanup() destroys all entities marked FLAG_DESTROY_PENDING.

## 13. Naming Conventions

| Category           | Convention                   | Example                              |
| ------------------ | ---------------------------- | ------------------------------------ |
| System function    | `system_<name>()`            | `system_ai_update()`                 |
| Component function | `<component>_add()`          | `timer_add()`                        |
| Intent function    | `<component>_try_<action>()` | `creature_try_move()`                |
| Event function     | `event_<action>()`           | `event_emit()`                       |
| Global data        | `g.<subsystem>`              | `g.entity`, `g.map`                  |
| Flags              | `FLAG_<NAME>`                | `FLAG_ALIVE`, `FLAG_DESTROY_PENDING` |

## 14. Performance Guidelines

Prefer static arrays over linked lists except for containers.

Keep systems O(n_active_entities) — no deep searches.

Avoid recursion; use iterative logic and small lookup tables.

Limit function call depth; inline where beneficial.

Use 8-bit integers wherever possible.

## 15. Design Philosophy

| **Layer**                                          | **May Contain / Reference**                              | **May Call / Access**                                                        | **Must Not Call / Access**                                                    | **Notes & Rationale**                                                                                                                     |
| -------------------------------------------------- | -------------------------------------------------------- | ---------------------------------------------------------------------------- | ----------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| **Entity Manager** (`entity.c`)                    | - Entity IDs<br>- Component masks<br>- Entity flags e.g. alive flag       | - Component add/remove helpers<br>- Component bitmask queries                | - System functions<br>- Direct game logic                                     | Manages entity lifecycle only. No gameplay logic — pure data ownership.                                                                   |
| **Components** (`component_*.c` / `component_*.h`) | - Raw data structs (position, health, timer, etc.)       | - Inline helpers: `*_add()`, `*_remove()`, `*_init()`                        | - Other components<br>- Systems<br>- Game logic                               | Components are **dumb data containers**. They can define small helpers to manipulate *their own* data only.                               |
| **Systems** (`system_*.c`)                         | - Arrays of components they operate on<br>- Entity masks | - The components they depend on<br>- Global systems via *explicit interface* | - Direct calls to other systems<br>- Creating/destroying entities arbitrarily | Systems implement behavior by processing entities with required components. They never know about “entities” beyond their component data. |
| **Game Loop / Scheduler** (`game.c`)               | - Global state and system list                           | - Systems (`system_update_*()`)                                              | - Components directly<br>- Entity internals                                   | Calls each system in turn. This is the only place that coordinates systems.                                                               |
| **Events / Messaging (optional)**                  | - Events / flags                                    | - Systems that subscribe                                                     | - Direct component access                                                     | Used to decouple system reactions (e.g., damage, death, sound).                                                                           |
| **Utility Modules** (`map.c`, `rng.c`, `path.c`)   | - Non-ECS data like map, RNG, path grid            | - Systems                                                                    | - Entities, components, or system state                                       | Used for external data that interacts with ECS but isn’t part of it.                                                                      |

## 16. Future Extensions

Pathfinding system (A* or Dijkstra) with caching per monster group.

FOV (field of view) and lighting system.

Status effect system driven by timers.

Simple scripting or event-driven encounters.

Persistent save/load of arena data to disk
