# Dungeon2 - ZX Spectrum Next Roguelike

**Target Platform**: ZX Spectrum Next
**Language**: C (z88dk toolchain)
**Architecture**: Entity-Component-System (ECS) optimized for 8-bit constraints

---

## Core Architecture Principles

This project uses a strict **Entity-Component-System** architecture. See [docs/architecture.md](docs/architecture.md) for complete details.

### Critical Rules

1. **Entities** are just IDs with flags - they contain NO data or logic
2. **Components** own data only - no logic, never call systems
3. **Systems** implement all game logic - operate on component arrays
4. **No dynamic allocation** - all memory is statically partitioned at compile time

### ECS Pattern

- Components are implemented as **arrays indexed by entity ID**: `component_data[entity_id]`
- Access controlled by component mask bitfields on entities
- Global state lives in: `__at (0x0000) static global_state_t g;`
- Prefer direct array indexing over pointers or lookups

### System Action Pattern

All gameplay systems follow this structure:

```c
bool system_try_xxx(...) {
    ctx_init(&c);    // Validate & gather data
    ctx_update(&c);  // Simulate & compute outcome
    ctx_apply(&c);   // Apply side effects
}
```

- **Try functions**: Check components, validate, call action functions, emit events, return bool
- **Action functions**: Assert components exist, execute action, always succeed (or abort)

### Entity Lifecycle

- Create: Use `entity_factory_create_monster()`, `entity_factory_create_item()`, etc.
- Destroy: **NEVER** destroy directly - use `entity_mark_for_destruction()`
- Cleanup runs in fixed order: container cleanup → AI cleanup → `entity_cleanup()`

---

## Naming Conventions

| Category | Convention | Example |
|----------|------------|---------|
| Functions | `snake_case` | `system_ai_update()` |
| Types | `snake_case_t` | `entity_id_t` |
| Struct fields | `snake_case` | `health.max_hp` |
| Macros/Constants | `UPPER_SNAKE_CASE` | `MAX_ENTITIES` |
| System functions | `system_<name>()` | `system_timer_update()` |
| Component functions | `<component>_<action>()` | `timer_add()` |
| Try functions | `<system>_try_<action>()` | `combat_system_try_melee_attack()` |
| Flags | `FLAG_<NAME>` | `FLAG_DESTROY_PENDING` |
| Global data | `g.<subsystem>` | `g.entity`, `g.map` |

---

## File Organization

```
/src
  /ecs
    /components   - Component definitions (*_comp.c, *_comp.h)
    /entity       - Entity lifecycle management
    /systems      - System implementations (*_system.c, *_system.h)
      /PAGEXX     - Memory-banked system code
  /core           - Generic utilities (math, graphics, input, text)
    /PAGEXX       - Memory-banked core code
  /game           - Game-specific code (world, dungeon gen, UI)
    /PAGEXX       - Memory-banked game code
```

### Component Rules (`*_comp.c/h`)

- Contain ONLY raw data and simple helpers that operate on that data
- Never call systems or contain game logic
- Must provide: `component_init()`, `component_add()`, `component_remove()`

### System Rules (`*_system.c/h`)

- Implement behavior by processing entities with required components
- Contain arrays of components they operate on
- May call other systems via well-defined entry points
- Should interact via events and component data where possible

### Core Rules

- Generic, reusable functionality (not game-specific)
- Examples: math, direction handling, graphics, input, text

### Game Rules

- Game-specific logic not part of ECS (map, mechanics, world rules)
- Should interact with systems via events and component data only

---

## Memory Banking (ZX Spectrum Next)

- Define page numbers in `zxnext.h`
- Create `/src/*/PAGEXX` directories for banked code
- Add dispatch functions in `systems_dispatch.c`
- **NEVER call banked code directly** - always use dispatch functions
- Update makefile to include new PAGEXX directories
- Manually create corresponding `/obj/PAGEXX` directories

---

## C Language Standards

- **Never use `int`** - use `uint8_t`, `int8_t`, `uint16_t`, etc.
- Use **8-bit integers** wherever possible (performance)
- **No magic numbers** - define constants
- Use `const` everywhere possible
- Validate inputs early, fail fast
- Use `util_assert()` for program invariants
- Return `false` for gameplay failures
- **No `malloc`** or dynamic memory allocation
- Use fixed-size arrays

---

## Build & Test

- **Build**: `make`
- Binary output: `bin/dungeon2_CODE.bin`
- Map file: `bin/dungeon2.map`

---

## Important Constraints

1. **Never modify `entity.c` to call systems or add game logic** - it only manages lifecycle
2. **Never destroy entities during iteration** - always mark for destruction
3. **Events represent things that happened** - not requests - process immediately
4. **Components never know about systems** - only systems know about components
5. **Memory is scarce** - ZX Spectrum constraints apply
6. **Function purity**: Init = no side effects, Update = validation only, Apply = mutation only
7. **No dynamic memory** - everything is statically allocated at compile time

---

## When Modifying Code

1. **Read existing code first** - understand patterns before changing
2. **Follow the try/action pattern** for all gameplay systems
3. **Emit events** when actions succeed
4. **Mark entities for destruction** - never destroy directly
5. **Keep systems isolated** - interact via component data and events
6. **Respect memory banks** - use dispatch functions for banked code
7. **Use component masks** - check before accessing component arrays
8. **Maintain separation**: Components = data, Systems = logic, Entity = lifecycle

---

## Performance Guidelines

- Use fixed-size arrays
- Systems can maintain entity lists for common iterations (avoid scanning all entities)
- Prefer direct array access over indirection
- 8-bit math is faster than 16-bit
- Memory locality matters - keep related data together
