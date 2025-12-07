# 🏁 **Traditional Roguelike Development Roadmap (ECS Architecture)**

## **Key**

* [ ]   Not started
* [🚧]  In Progress
* [✅]   Completed

---

## 🪜 **Milestone 1XX - Core game mechanics**

### 🪜 **Milestone 101 — Core Engine Online**

> *Goal: get entities, components, and the game loop running in memory.*

* [✅] Implement `entity_id_t` and `entity_t` structs
* [✅] Implement `entity_create()` / `entity_destroy()`
* [✅] Add free-list or active-list allocator
* [✅] Add `Location` and `Renderable` components - implement helper functions e.g. add() and remove()
* [✅] Remove components on entity destroy
* [✅] Create ECS system iteration (loop through active entities)
* [✅] Implement `render_system()` to draw a test entity
* [✅] Build a fixed arena at a known base address (e.g. 0x0000)
* [✅] Display a single `'@'` on screen

[✅] *End result: a single player entity renders successfully.*

---

### 🪜 **Milestone 102 — A Map**

> *Goal: basic map & movement mechanics.*

* [✅] Implement map_terrain
* [✅] Implement entities list at map x, y
* [✅] Implement map which is a composite of map_terrain and entity lists
* [✅] `map_is_walkable(x, y)` with checks for terrain

[✅] *End result: '@' moves around a dungeon grid.*

---

### 🪜 **Milestone 103 — Entity Spawning**

> *Goal: multiple creatures and items exist on the map.*

* [✅] Add `Creature` and `Item` components  - implement helper functions e.g. add() and remove()
* [✅] Implement entity factory to spawn creatures
* [✅] Implement entity factory to spawn items
* [✅] Implement creature base
* [✅] Implement item base
* [✅] Render monsters (`'g'`, `'r'`, etc.) and items (`'!'`, `')'`)
* [✅] Remove creature and item components on entity destroy
* [✅] Prevent walking through blocking monsters and items
* [✅] Refactor entity factory code to spawn monsters not creatures - monsters are more than a creature component
* [✅] Refactor entity factory code to spawn equipment not items - equipment is more than an item component

[✅] *End result: '@' can walk around rooms with visible creatures and items.*

---

### 🪜 **Milestone 104 — Turn System & Timers**

> *Goal: establish turn-based logic and per-entity speed.*

* [✅] Add `Timer` component (turns + ticks)  - implement helper functions e.g. add(), remove(), set(), reset(), and tick()
* [✅] Implement `Timer` system, timers decrease and set fired flag when they expire
* [✅] Remove component on entity destroy

[✅] *End result: Entities have one shot timer that controls their turn.*

---

### 🪜 **Milestone 104b — Implement moving @**

> *Goal: basic map & movement mechanics.*

* [✅] Add player `movement` commands (arrow keys or numpad)
* [✅] Move player entity across map tiles
* [✅] Prevent walking through walls

[✅] *End result: '@' moves around a dungeon grid.*

---

### 🪜 **Milestone 105 — Basic Melee Combat & Events**

> *Goal: entities can attack and die.*

* [✅] Add player `melee attack` command
* [✅] Implement `creature_try_melee_attack` - basic creature melee attack
* [✅] Implement `creature_try_take_damage` - apply damage amount
* [✅] Add `EVENT_ATTACKED`
* [✅] Add `event_entity_damaged`
* [✅] Add `EVENT_DIED`
* [✅] Add message log system for attack, damage and death events e.g. (“You hit the rat.”)

[✅] *End result: You can attack and kill monsters.*

---

### 🪜 **Milestone 106 — Containers**

> *Goal: implement container mechanic for use by chests, inventory etc.*

* [✅] Add `Container` component
* [✅] Add `Contained` component
* [✅] Implement Container System
* [✅] Implement maximum number of items in container
* [✅] Cleanup and flag contained components to be destroyed when container entity is destroyed
* [✅] Remove container and contained components on entity destroy

[✅] *End result: An entity can contain other items.*

---

### 🪜 **Milestone 107a — Player Inventory**

> *Goal: inventory management.*

* [✅] Add `view inventory` command
* [✅] Implement view inventory window (list container entities)
* [✅] Implement `uint8_t prompt_letter(uint8_t max_index)` input - returns the selected item or if the player cancelled

[✅] *End result: Player can view inventory and drop an item from inventory.*

---

### 🪜 **Milestone 107b — Pickup**

> *Goal: implement pickup action*

* [✅] Add player `pickup` command
* [ ] Add selection mechanic if there are multiple items on the tile
* [✅] Implement `creature_try_pickup()`
* [✅] Add `event_picked_up`
* [✅] Add message log system for pick up events e.g. (“You pickup the potion.”)

[ ] *End result: Player can pick up items.*

### 🪜 **Milestone 107c — Drop**

> *Goal: implement drop action*

* [✅] Add player `drop` command
* [✅] Add mechanic to select item to drop from inventory
* [✅] Implement `creature_try_drop()`
* [✅] Add `event_dropped_up`
* [✅] Add message log system for pick up events e.g. (“You drop the potion.”)

[✅] *End result: Player can drop items.*

### 🪜 **Milestone 108 — Player Equipment**

> *Goal: PLayer can equip and unequip items*

* [✅] Add `Equipment` component - this is a player only component
* [✅] Implement slot for melee weapon and ranged weapon
* [✅] Implement one slot for quiver (ammo)
* [✅] Implement slots for head (helmet), body (body armour), legs, feet (shoes/boots)
* [✅] Implement two slots for fingers (rings), neck (necklace)
* [✅] Update view inventory window to show equipped items
* [✅] Add player `equip` command - select from inventory
* [ ] Add player `unequip` command - select slot
* [✅] Implement `player_try_equip()` - try to remove entity from inventory and place in slot
* [ ] Implement `player_try_unequip()` - try to remove entity from slot and place in inventory
* [✅] Add `event_item_equipped`
* [ ] Add `event_item_unequipped`
* [ ] Automatically try unequipping an item from a slot when equipping
* [ ] Manage dropping equiped items
* [ ] Destroy equipment component on entity destroy
* [ ] Add message log system for equip and unequip events e.g. (“You equip the sword.”)

[ ] *End result: Player can equip and uneqip items.*

---

### 🪜 **Milestone 109 — Creature resistance and immunity**

> *Goal: Creature can have damage resistence and immunity*

* [ ] Add `Resistance` component - implement helper functions e.g. add(), remove(), set() and clear()
* [ ] Update damage calculation to take resistance and immunity into account
* [ ] Remove resistance component on entity destroy

[ ] *End result: Damage calculation takes creature's resistance and immunity into account.*

---

### 🪜 **Milestone 110 — Basic targetting and line of sight**

> *Goal: entities can target.*

* [ ] Add player `look` command (examine tile/entity)
* [ ] Implement player target selection input
* [ ] Implement line of sight test
* [ ] Implement `player_try_look()`

[ ] *End result: Player can target a tile and examine a tile/entity if in line of sight.*

### 🪜 **Milestone 111 — Basic Ranged Combat & Events**

> *Goal: entities can range attack.*

* [ ] Add player `fire` command (ranged attack)
* [ ] Implement basic `creature_try_ranged_attack()`

[ ] *End result: You can range attack and kill monsters.*

---

### 🪜 **Milestone 112 — A Camera**

> *Goal: camera follows player as they move around the map.*

* [✅] Implement larger map
* [ ] Implement camera position and ability to pan camera
* [ ] Implement camera following player

[ ] *End result: camera follows player.*

---

### 🪜 **Milestone 113 — Experience and levelling up**

> *Goal: Player gains experience and level up.*

* [ ] Implement player experience
* [ ] Implement gain experience
* [ ] Implement player levels
* [ ] Implement player levelling up

[ ] *End result: player gains experience and levels up.*

---

### 🪜 **Milestone 114 — Entity naming**

> *Goal: Entities have names*

* [ ] Implement `name` component - implement helper functions e.g. add() and remove()
* [ ] Implement add() copies from base

[ ] *End result: entities have a name component.*

### 🪜 **Milestone 115 — Implement steppable entities*

> *Goal: Entities can react to being stood on*

* [ ] Add `Steppable` component with step_effect and single_use
* [ ] Add `EVENT_STOOD_ON` event
* [ ] Update movement system to check for entities at entered location and emit an `EVENT_STOOD_ON` for each
* [ ] Inplement steppable_system
* [ ] Implement `steppable_system_on_stood_on()`to handle events e.g. check for stappable component and take action
* [ ] Implement trap feature
* [ ] Add message log system for stood on events e.g. (“You stood on the trap.”)
* [ ] Remove steppable components on entity destroy

[ ] *End result: Traps react to being stood on*

### 🪜 **Milestone 116 — Implement bumpable entities*

> *Goal: Entities can react to bumped into*

[ ] *End result: Unlocked doors open if you walk into them*

## 🪜 **Milestone 2XX — Items**

### 🪜 **Milestone 201 — Food**

> *Goal: eat food to restore health.*

* [ ] Implement food items - apple & bread
* [ ] Add player `eat` command - select from inventory
* [ ] Implement `creature_try_eat()`
* [ ] Implement `creature_consume_food()`
* [ ] Implement `try_restore_health()` - add hp up to max_hp
* [ ] Add `event_food_consumed`
* [ ] Add message log system for food consumed events e.g. (“You eat the apple.”)

[ ] *End result: Player can restore health by eating food and food is destroyed.*

---

### 🪜 **Milestone 202 — Potions**

> *Goal: PLayer can quaff potions*

* [ ] Implement potion items - restore health & poison
* [ ] Add player `quaff` command - select from inventory
* [ ] Implement `creature_try_quaf()`
* [ ] Implement `creeature_quaff_potion()`
* [ ] Add `event_consumed_potion`
* [ ] Add message log system for potion quaffed events e.g. (“You quaff the potion of healing.”)

[ ] *End result: Potion is destroyed and any effect applied.*

---

### 🪜 **Milestone 203 — Melee combat**

> *Goal: Implement melee combat*

* [ ] Implement melee weapon equipment - dagger & sword
* [ ] Implement melee attack component
* [ ] Implement default melee attack component for creatures
* [ ] Separate weapon's to hit and to damage bonus from creature's to hit and to damage bonus
* [ ] Implement ability to equip and unequip melee weapons
* [ ] Implement `actions_system_try_melee_attack()` - use equipped melee or default melee if not
* [ ] Implement `actions_system_try_melee_attack()`- add

[ ] *End result: Player can equip a melee weapon and melee attack stats are updated.*

---

### 🪜 **Milestone 204 — Armour**

> *Goal: Player can equip armour*

* [ ] Implement armour items - leather helmet, leather body armour, leather boots
* [ ] Implement ability to equip and unequip armour (tbc implement base AC)
* [ ] Implement player stat recalculation for armour

[ ] *End result: Player can equip armour and stats are updated.*

---

## 🪜 **Milestone 3XX — Monster AI**

### 🪜 **Milestone 301 — Basic Monster AI System**

> *Goal: monsters can act intelligently.*

* [ ] Add `AI_CTRL` component - implement helper functions e.g. add() and remove()
* [ ] Define `ai_state_t`
* [ ] Implement `ai_on_event()` to process events and transition between states
* [ ] Add `ai_system_update()` - entity takes it turn
* [ ] Implement `ai_sleep_state()` - monster does nothing
* [ ] Implement `ai_guard_state()` - monster will melee attack a creature in range

[ ] *End result: Monsters can attack the player.*

---

### 🪜 **Milestone 301 — Wandering state**

> *Goal: monsters can wander.*

* [ ] Implement `ai_wandering_state()` - monster performs 'drunk' walk

[ ] *End result: Monsters can drunken walk.*

---

## 🪜 **Milestone 4XX — Features**

### 🪜 **Milestone 401 — Dungeon features and basic doors**

> *Goal: dungeons can have features that can be interacted with.*

* [] Add `Feature` component  - implement helper functions e.g. add() and remove()
* [] Implement entity factory to spawn features
* [] Implement feature base
* [ ] Implement a basic door feature
* [ ] Add player `open` command for doors
* [ ] Add player `close` command for doors
* [ ] Implement `try_open_door()` for door
* [ ] Implement `try_close_door()` for door
* [ ] Add `event_door_opened`
* [ ] Add `event_door_closed`
* [ ] Prevent walking through closed doors
* [ ] Destroy feature component on entity destroy
* [ ] Add message log system for open/close door events e.g. (“You open the door.”)

[ ] *End result: Player can open and close basic doors.*

---

### 🪜 **Milestone 402 — Basic Chests**

> *Goal: chests can be opened and closed and items taken out.*

* [ ] Implement a basic chest feature
* [ ] Add player `open` command for chests
* [ ] Implement `try_open_chest()` for chest
* [ ] Add `event_chest_opened`
* [ ] Implement chest inventory and ability to take an item
* [ ] Add message log system for opening chest and taking items e.g. (“You open the chest.”, "You take the ring.")

[ ] *End result: Player can open chest and take items.*

---

### 🪜 **Milestone 403 — Up and down stairs**

> *Goal: Can climb stairs.*

* [ ] Implement up and down stair features
* [ ] Add player `climb` command for stairs
* [ ] Implement `try_climb()` for stairs
* [ ] Add `event_ascend_stairs` and `event_descend_stairs`
* [ ] Implement chest inventory and ability to take an item
* [ ] Add message log system for opening chest and taking items e.g. (“You open the chest.”, "You take the ring.")

[ ] *End result: Player can open chest and take items.*

---

## 🪜 **Milestone 5XX — Dungeon Generation & Progression**

### 🪜 **Milestone 501 — Dungeon Generation**

> *Goal: procedural dungeon generator.*

* [✅] Implement procedural map generator (rooms + corridors)
* [ ] Place stairs up/down
* [ ] Place player
* [ ] Add new monsters per depth
* [ ] Add new items per depth
* [ ] Add new features per depth

[ ] *End result: Dungeon with rooms, corridors and populated with entities.*

---

### 🪜 **Milestone 502 — Dungeon level transistion**

> *Goal: handle depth transistions (load next map).*

* [ ] Implement persistent entities with level
* [ ] Implement persistance entity check (recursive)
* [ ] Implement deletion of non persistent entities
* [ ] Implement depth change including moving player to new depth
* [ ] Update map generator to place persitent entities on level
* [ ] Call map generator

[ ] *End result: Able to transistion levels and persistent entities are retained.*

---

## 🪜 **Milestone 6XX — UI, Messages & Status**

### 🪜 **Milestone 601 — Message log UI**

> *Goal: Display messages in response to game events.*

* [✅] Implement message log window
* [ ] Implement 'press key to continue' if messages exceeds window size before players next turn

[ ] *End result: Player is notified of game events.*

### 🪜 **Milestone 602 — Status UI**

> *Goal: Display player status.*

* [ ] Display player status (HP, depth etc)

[ ] *End result: Player can see current status.*

---

## 🪜 **Milestone 7XX — Performance and Stability**

### 🪜 **Milestone 700 — Performance**

> *Goal: optimize for speed and memory.*

* [ ] Implement optimised active entity iteration (if used)
* [ ] Optimse clean up of entities flagged for destruction e.g. set and check flag for when there are entities flagged to be destroyed
* [ ] Optimse clean up of container system e.g. set and check flag for when there are entities flagged to be destroyed
* [ ] Optimse the core game loop by only re-drawing map when needed e.g. only redraw when updated and players turn
* [ ] Optimse the core game loop by only re-drawing the stats window
* [ ] Optimse the core game loop by optimising timer system iteration

[ ] *End result: Smooth play experience on Spectrum Next.*

### 🪜 **Milestone 700 — Game data structure verification**

> *Goal: game data structure is in valid state.*

* [✅] Implement assert() global game struct is less than 16KB
* [ ] Implement global data structure validation tests

[ ] *End result: data structure validation tests pass.*

---

## 🪜 **Milestone 1000 — Game Finish & Presentation**

> *Goal: complete game loop and polish.*

* [ ] Add victory condition (retrieve Amulet, etc.)
* [ ] Add title screen and logo
* [ ] Add sound effects
* [ ] Add death screen
* [ ] Credits / end text

[ ] *End result: Fully playable, finished roguelike.*

---

## 🧰 Optional Enhancements

* [ ] Save/load game state
* [ ] Dynamic lighting or FOV
* [ ] Ranged attacks and projectiles
* [ ] Spellcasting system
* [ ] Equipment and inventory weights
* [ ] Procedural names/descriptions
* [ ] Multiple dungeon themes

---
