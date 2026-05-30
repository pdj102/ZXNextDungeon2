Dungeon 2 for the Spectrum Next
See dev branch for latest WIP version

Target platform: ZX Spectrum Next
Language: C (z88dk or SDCC toolchain)

1. ECS Architecture 
The engine uses an Entity-Component-System (ECS) model optimized for 8-bit constraints, emphasizing data locality, deterministic updates, and low CPU overhead.

2. Core Concepts
Entities:
    Entities represent unique game objects (player, monsters, items, map features, etc.).
    Identified by a small integer ID (entity_id_t)
    Entities own no data
    Entities contain no game logic, only an ID and limited flags.
    MAX_ENTITIES defines the maximum number of entities
    ENTITY_ID_INVALID refers to an invalid entity ID

Components:
    Components own data for one aspect of an entity e.g. position, AI, health, timer, container.
    Components contain only data and simple helper functions (no logic) that only operate on the component's data
    Components never call systems
    Implemented as arrays for efficient access:
        location_t location[MAX_ENTITIES];
        health_t health[MAX_ENTITIES];
    Access to components is controlled by a mask bitfield on the entity.

Systems:
    Perform logic over entities that have specific combinations of components.
    Examples:
        system_timer() – advances entity timers.
    Gameplay systems follow the following structure 
    bool system_try_xxx(...) 
    {
      ctx c;  // context struct
      ctx_init(&c); // Validate & gather data 
      ctx_update(&c); // Simulate action & compute outcome
      ctx_apply(&c); // Apply calculated outcome
    }
