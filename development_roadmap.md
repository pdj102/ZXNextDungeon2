# 🏁 **Traditional Roguelike Development Roadmap (ECS Architecture)**

## **Key**

* [ ]   Not started
* [🚧]  In Progress
* [✅]   Completed

---

## 🪜 **Milestone 1 — Core Engine Online**

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

## 🪜 **Milestone 2 — Moving '@' on a Map**

> *Goal: basic map & movement mechanics.*

* [✅] Define `map_t` with terrain array
* [✅] Implement terrain
* [✅] Implement entity list at x, y 
* [✅] `map_is_walkable(x, y)` and boundary checks for terrain
* [✅] Handle player input (arrow keys or numpad)
* [✅] Move player entity across map tiles
* [✅] Prevent walking through walls
  ✅ *End result: '@' moves around a dungeon grid.*

---

## 🪜 **Milestone 3 — Entity Spawning**

> *Goal: multiple creatures and items exist on the map.*

* [✅] Add `Creature` and `Item` components  - implement helper functions e.g. add() and remove()
* [✅] Implement entity factory to spawn creatures
* [✅] Implement entity factory to spawn items
* [✅] Render monsters (`'g'`, `'r'`, etc.) and items (`'!'`, `')'`)
* [✅] Remove components on entity destroy
* [ ] Prevent walking through blocking monsters and items
* [ ] Basic FOV (optional, for performance)
  ✅ *End result: '@' can walk around rooms with visible creatures and items.*

---

## 🪜 **Milestone 4 — Turn System & Timers**

> *Goal: establish turn-based logic and per-entity speed.*

* [✅] Add `Timer` component (turns + ticks)  - implement helper functions e.g. add() and remove()
* [✅] Implement global turn counter
* [✅] Player and monsters acts when timer expires
* [✅] Remove component on entity destroy
* [✅] Add deferred destruction and alive flag
  ✅ *End result: Player → Monster → Player sequence is functional.*

---

## 🪜 **Milestone 5 — Basic Melee Combat & Events**

> *Goal: entities can attack and die.*

* [ ] Implement basic creature melee attack
* [ ] Implement basic creature take damage
* [ ] Add `event_entity_attacked`
* [ ] Add `event_entity_damaged`
* [ ] Add `event_entity_died`
* [ ] Add message log system for attack, damage and death events e.g. (“You hit the rat.”)
  ✅ *End result: You can attack and kill monsters.*

---

## 🪜 **Milestone 6 — Inventory & Items**

> *Goal: pickup and drop items.*

* [✅] Add `Container` component
* [✅] Add `Contained` component
* [✅] Implement `try_pickup()`
* [✅] Implement `try_drop()`
* [✅] Add `event_picked_up`
* [✅] Add `event_dropped`
* [ ] Implement inventory window (simple list)
* [ ] Implement item selection from inventory
* [ ] Implement maximum number of items in container
* [ ] Destroy contained components on container entity destroy
* [✅] Remove components on entity destroy
* [✅] Add message log system for pick up and drop events e.g. (“You drop the potion.”)
  ✅ *End result: Player can pick up and drop items.*

---

## 🪜 **Milestone 7 — Basic Doors**

> *Goal: open and close doors.*

* [ ] Add `Door` component
* [ ] Implement `try_open()` for door
* [ ] Implement `try_close()` for door
* [ ] Add `event_door_opened`
* [ ] Add `event_door_closed`
* [ ] Prevent walking through closed doors
* [ ] Destroy component on entity destroy
* [ ] Add message log system for pick up and drop events e.g. (“You open the door.”)
✅ *End result: Player can open and close basic doors.*

---

## 🪜 **Milestone 8 — Player Equipment**

> *Goal: PLayer can equip and unequip items*

* [ ] Add 'Equipment' component - this is a player only component
* [ ] Implement slots for hands (melee weapon, ranged weapon and shield)
* [ ] Implement slot for quiver (ammo)
* [ ] Implement slots for head (helmet), armour, feet (shoes/boots)
* [ ] Implement slots for fingers (rings), neck (necklace)
* [ ] Implement `try_equip()`
* [ ] Implement `try_unequip()`
* [ ] Add `event_item_equipped`
* [ ] Add `event_item_unequipped`
* [ ] Automatically try unequipping an item if item already in the slot when equipping
* [ ] Destroy component on entity destroy
* [ ] Add message log system for equip and unequip events e.g. (“You equip the sword.”)
✅ *End result: Player can equip and uneqip items.*

---

## 🪜 **Milestone 9 — Player equipment stat modifier system**

> *Goal: PLayer stats are modified by equipment*

* [ ] Implement `equipement system`
* [ ] `event_item_equipped` and `event_item_unequipped` trigger recalculation of player stats and resistance/immunity

✅ *End result: Player stats are automatically modified by equipping and removing equipment.*

---

## 🪜 **Milestone 10 — Potions**

> *Goal: PLayer can quaff potions*

* [ ] Implement potion items
* [ ] Implement `try_quaf()`
* [ ] Implement `consume_potion()`
* [ ] Add `event_consumed_potion`

✅ *End result: Potion is destroyed and any effect applied.*

---

## 🪜 **Milestone 11 — Creature resistance and immunity**

> *Goal: Creature can have damage resistence and immunity*

* [ ] Add `Resistance` component - implement helper functions e.g. add(), remove(), set() and clear()
* [ ] Update damage calculation to take resistance and immunity into account
* [ ] Remove component on entity destroy
✅ *End result: Damage calculation takes creature's resistance and immunity into account.*

---

## 🪜 **Milestone 12 — Melee weapons**

> *Goal: Player can weild melee weapons*

* [ ] Implement melee weapon items
* [ ] Implement ability to equip and unequip melee weapons
* [ ] Implement player stat recalculation for melee weapons

✅ *End result: Player can equip a melee weapon and melee attack stats are updated.*

---

## 🪜 **Milestone 13 — Armour**

> *Goal: Player can equip armour*

* [ ] Implement armour items
* [ ] Implement ability to equip and unequip armour
* [ ] Implement player stat recalculation for armour

✅ *End result: Player can equip armour and stats are updated.*

---

## 🪜 **Milestone 101 — Monster AI**

> *Goal: monsters can act intelligently.*

* [ ] Add `AI` component
* [ ] Implement `ai_chase_player()`
* [ ] Implement random wandering when idle
* [ ] Add sight checks or simple distance triggers
  ✅ *End result: Monsters move toward and attack the player.*

---

## 🪜 **Milestone 201 — Ranged Combat & Events**

> *Goal: entities can range attack.*

* [ ] Implement targetting system
* [ ] Implement basic ranged attack
* [ ] Implement anumition usage for ranged attacks
  ✅ *End result: You can range attack and kill monsters.*

---


## 🪜 **Milestone 300 — Game Loop Polish**

> *Goal: complete gameplay cycle and turn sequencing.*

* [ ] Integrate all systems: input → ECS → render
* [ ] Ensure timers and turns sync correctly
* [ ] Handle deferred destruction safely
* [ ] Ensure no entity ID reuse bugs
  ✅ *End result: Fully playable short dungeon run.*

---

## 🪜 **Milestone 400 — Dungeon Generation & Progression**

> *Goal: explore multiple dungeon floors.*

* [ ] Implement procedural map generator (rooms + corridors)
* [ ] Place stairs up/down
* [ ] Handle depth transitions (load next map)
* [ ] Add new monsters per depth
  ✅ *End result: Multi-level dungeon with new monsters per level.*

---

## 🪜 **Milestone 500 — UI, Messages & Status**

> *Goal: a proper roguelike interface.*

* [ ] Add status bar (HP, depth, turn #)
* [ ] Implement scrolling message log
* [ ] Add color and tile graphics (Spectrum Next palette)
* [ ] Add “look” command (examine tile/entity)
  ✅ *End result: Full playable interface with feedback.*

---

## 🪜 **Milestone 600 — Performance & Stability**

> *Goal: optimize for 8-bit constraints.*

* [ ] Profile CPU cycles per frame
* [ ] Optimize ECS iteration (active list)
* [ ] Compress entity data structures
* [ ] Optimse when and what parts of the map are redrawn e.g. only redraw when updated and players turn
* [ ] Optimse deffered destruction of entities e.g. list of entities that need to be destroyed
* [ ] Verify memory usage stays within limit
  ✅ *End result: Smooth 50 Hz play experience on Spectrum Next.*

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
