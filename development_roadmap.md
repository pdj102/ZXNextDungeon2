# 🏁 **Traditional Roguelike Development Roadmap (ECS Architecture)**

## **Key**

* [ ]   Not started
* [🚧]  In Progress
* [✅]   Completed

---

## 🪜 **Milestone 1XX - Core game mechanics**

## 🪜 **Milestone 101 — Core Engine Online**

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
  ✅ *End result: a single player entity renders successfully.*

---

## 🪜 **Milestone 102 — Moving '@' on a Map**

> *Goal: basic map & movement mechanics.*

* [✅] Define `map_t` with terrain array
* [✅] Implement terrain
* [✅] Implement entity list at x, y
* [✅] `map_is_walkable(x, y)` and boundary checks for terrain
* [✅] Add player `movement` commands (arrow keys or numpad)
* [✅] Move player entity across map tiles
* [✅] Prevent walking through walls
  ✅ *End result: '@' moves around a dungeon grid.*

---

## 🪜 **Milestone 103 — Entity Spawning**

> *Goal: multiple creatures and items exist on the map.*

* [✅] Add `Creature` and `Item` components  - implement helper functions e.g. add() and remove()
* [✅] Implement entity factory to spawn monsters
* [✅] Implement entity factory to spawn items
* [✅] Implement creature base
* [✅] Implement item base
* [✅] Render monsters (`'g'`, `'r'`, etc.) and items (`'!'`, `')'`)
* [✅] Remove creature and item components on entity destroy
* [ ] Prevent walking through blocking monsters and items
* [ ] Basic FOV (optional, for performance)
  ✅ *End result: '@' can walk around rooms with visible creatures and items.*

---

## 🪜 **Milestone 104 — Turn System & Timers**

> *Goal: establish turn-based logic and per-entity speed.*

* [✅] Add `Timer` component (turns + ticks)  - implement helper functions e.g. add() and remove()
* [✅] Implement global turn counter
* [✅] Player and monsters acts when timer expires
* [✅] Remove component on entity destroy
* [✅] Add deferred destruction and alive flag
  ✅ *End result: Player → Monster → Player sequence is functional.*

---

## 🪜 **Milestone 105 — Basic Melee Combat & Events**

> *Goal: entities can attack and die.*

* [ ] Add player `melee attack` command
* [ ] Implement `creature_try_melee_attack` - basic creature melee attack
* [ ] Implement `creature_try_take_damage` - apply damage amount
* [ ] Add `event_entity_attacked`
* [ ] Add `event_entity_damaged`
* [ ] Add `event_entity_died`
* [ ] Add message log system for attack, damage and death events e.g. (“You hit the rat.”)
  ✅ *End result: You can attack and kill monsters.*

---

## 🪜 **Milestone 106 — Containers**

> *Goal: implement container mechanic for use by chests, inventory etc.*

* [✅] Add `Container` component
* [✅] Add `Contained` component
* [✅] Add player `pickup` and `drop` commands
* [✅] Implement `creature_try_pickup()`
* [✅] Implement `creature_try_drop()`
* [✅] Add `event_picked_up`
* [✅] Add `event_dropped`
* [ ] Implement maximum number of items in container
* [ ] Destroy contained components when container entity is destroyed
* [✅] Remove container and contained components on entity destroy
* [✅] Add message log system for pick up and drop events e.g. (“You drop the potion.”)
  ✅ *End result: An entity can contain other items and player can pick up and drop items.*

---

## 🪜 **Milestone 107 — Player Inventory**

> *Goal: inventory management.*

* [✅] Add `view inventory` command
* [✅] Update player `drop` command to select item from inventory
* [ ] Implement inventory window (list container entities)
* [ ] Implement player `item selection` input - select entity from container list or cancel
  ✅ *End result: Player can view inventory and drop an item from inventory.*

---

## 🪜 **Milestone 108 — Player Equipment**

> *Goal: PLayer can equip and unequip items*

* [ ] Add `Equipment` component - this is a player only component
* [ ] Implement slots for hands (melee weapon, ranged weapon and shield)
* [ ] Implement slot for quiver (ammo)
* [ ] Implement slots for head (helmet), body (body armour), feet (shoes/boots)
* [ ] Implement slots for fingers (rings), neck (necklace)
* [ ] Add player `equip` command - select from inventory
* [ ] Add player `unequip` command - select slot
* [ ] Implement `player_try_equip()` - try to remove entity from inventory and place in slot
* [ ] Implement `player_try_unequip()` - try to remove entity from slot and place in inventory
* [ ] Add `event_item_equipped`
* [ ] Add `event_item_unequipped`
* [ ] Automatically try unequipping an item from a slot when equipping
* [ ] Destroy equipment component on entity destroy
* [ ] Add message log system for equip and unequip events e.g. (“You equip the sword.”)
✅ *End result: Player can equip and uneqip items.*

---

## 🪜 **Milestone 109 — Creature resistance and immunity**

> *Goal: Creature can have damage resistence and immunity*

* [ ] Add `Resistance` component - implement helper functions e.g. add(), remove(), set() and clear()
* [ ] Update damage calculation to take resistance and immunity into account
* [ ] Remove resistance component on entity destroy
✅ *End result: Damage calculation takes creature's resistance and immunity into account.*

---

## 🪜 **Milestone 110 — Basic targetting and line of sight**

> *Goal: entities can target.*

* [ ] Add player `look` command (examine tile/entity)
* [ ] Implement player target selection input
* [ ] Implement line of sight test
* [ ] Implement `player_try_look()`
  ✅ *End result: Player can target a tile and examine a tile/entity if in line of sight.*

## 🪜 **Milestone 111 — Basic Ranged Combat & Events**

> *Goal: entities can range attack.*

* [ ] Add player `fire` command (ranged attack)
* [ ] Implement basic `creature_try_ranged_attack()`
  ✅ *End result: You can range attack and kill monsters.*

---

## 🪜 **Milestone 2XX — Items**

## 🪜 **Milestone 201 — Food**

> *Goal: eat food to restore health.*

* [ ] Implement food items
* [ ] Implement `creature_try_eat()`
* [ ] Implement `creature_consume_food()`
* [ ] Implement `try_restore_health()` - add hp up to max_hp
* [ ] Add `event_food_consumed`
* [ ] Add message log system for food consumed events e.g. (“You eat the apple.”)
✅ *End result: Player can restore health by eating food and food is destroyed.*

---

## 🪜 **Milestone 202 — Potions**

> *Goal: PLayer can quaff potions*

* [ ] Implement potion items
* [ ] Implement `creature_try_quaf()`
* [ ] Implement `creeature_quaff_potion()`
* [ ] Add `event_consumed_potion`
* [ ] Add message log system for potion quaffed events e.g. (“You quaff the potion of healing.”)
✅ *End result: Potion is destroyed and any effect applied.*

---

## 🪜 **Milestone 203 — Melee weapons**

> *Goal: Player can weild melee weapons*

* [ ] Implement melee weapon items
* [ ] Implement ability to equip and unequip melee weapons
* [ ] Implement player stat recalculation for melee weapons

✅ *End result: Player can equip a melee weapon and melee attack stats are updated.*

---

## 🪜 **Milestone 204 — Armour**

> *Goal: Player can equip armour*

* [ ] Implement armour items - helmets, body armour, boots/shoes
* [ ] Implement ability to equip and unequip armour
* [ ] Implement player stat recalculation for armour

✅ *End result: Player can equip armour and stats are updated.*

---

## 🪜 **Milestone 205 — Monster AI**

> *Goal: monsters can act intelligently.*

* [ ] Add `AI` component
* [ ] Implement `ai_chase_player()`
* [ ] Implement random wandering when idle
* [ ] Add sight checks or simple distance triggers
  ✅ *End result: Monsters move toward and attack the player.*

---

## 🪜 **Milestone 3XX — Features**

## 🪜 **Milestone 301 — Basic Doors**

> *Goal: open and close doors.*

* [ ] Add `Feature` component
* [ ] Implement `try_open()` for door
* [ ] Implement `try_close()` for door
* [ ] Add `event_door_opened`
* [ ] Add `event_door_closed`
* [ ] Prevent walking through closed doors
* [ ] Destroy feature component on entity destroy
* [ ] Add message log system for pick up and drop events e.g. (“You open the door.”)
✅ *End result: Player can open and close basic doors.*

## 🪜 **Milestone 302 — Basic Chests**

> *Goal: chests can be opened and closed and items taken out.*

* [ ] Implement `try_open()` for chest
* [ ] Add `event_chest_opened`
* [ ] Implement chest inventory and ability to take an item
* [ ] Add message log system for opening chest and taking items e.g. (“You open the chest.”, "You take the ring.")
✅ *End result: Player can open chest and take items.*

---

## 🪜 **Milestone 4XX — Performance and Stability**

---

## 🪜 **Milestone 700 — Performance**

> *Goal: optimize for speed and memory.*

* [ ] Implement optimised active entity iteration (if used)
* [ ] Implement optimised iteration of entities at map x, y
* [ ] Optimse deffered destruction of entities e.g. list of entities that need to be destroyed
* [ ] Optimse the core game loop by only re-drawing map when needed e.g. only redraw when updated and players turn
* [ ] Optimse the core game loop by only re-drawing the stats window
* [ ] Optimse the core game loop by optimising timer system iteration
  ✅ *End result: Smooth play experience on Spectrum Next.*

  ## 🪜 **Milestone 700 — Game data structure verification**

> *Goal: game data structure is in valid state.*

  ✅ *End result: data structure validation tests pass.*

## 🪜 **Milestone 5XX — Dungeon Generation & Progression**

## 🪜 **Milestone 501 — Dungeon Generation**

> *Goal: procedural map generator.*

* [ ] Implement procedural map generator (rooms + corridors)
* [ ] Place stairs up/down
* [ ] Place player
* [ ] Add new monsters per depth
* [ ] Add new items per depth
* [ ] Add new features per depth
  ✅ *End result: Dungeon with rooms, corridors and populated with entities.*

---

## 🪜 **Milestone 502 — Dungeon level transistion**

> *Goal: handle depth transistions (load next map).*

* [ ] Implement persistent entities with level
* [ ] Implement persistance entity check (recursive)
* [ ] Implement deletion of non persistent entities
* [ ] Implement depth change including moving player to new depth
* [ ] Update map generator to place persitent entities on level
* [ ] Call map generator
✅ *End result: Able to transistion levels and persistent entities are retained.*

## 🪜 **Milestone 600 — UI, Messages & Status**

> *Goal: a proper roguelike interface.*

* [ ] Add status bar (HP, depth, turn #)
* [ ] Implement scrolling message log
* [ ] Add color and tile graphics (Spectrum Next palette)
* [ ] Add “look” command (examine tile/entity)
  ✅ *End result: Full playable interface with feedback.*

---

## 🪜 **Milestone 1000 — Game Finish & Presentation**

> *Goal: complete game loop and polish.*

* [ ] Add victory condition (retrieve Amulet, etc.)
* [ ] Add title screen and logo
* [ ] Add sound effects
* [ ] Add death screen
* [ ] Credits / end text
  ✅ *End result: Fully playable, finished roguelike.*

---

## 🧰 Optional Enhancements

* [ ] Save/load game state
* [ ] Dynamic lighting or FOV
* [ ] Ranged attacks and projectiles
* [ ] Spellcasting system
* [ ] Equipment and inventory weights
* [ ] Procedural names/descriptions
* [ ] Multiple dungeon themes
* [ ] Add `Name` components (decide if needed or not)

---

Would you like me to extend this with a **suggested implementation order** for your code files (e.g. which `.c`/`.h` files to create and in what order to build them up)?
That would make it a practical project plan for starting coding.
