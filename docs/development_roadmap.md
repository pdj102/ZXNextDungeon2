# 🏁 **Traditional Roguelike Development Roadmap (ECS Architecture)**

## **Key**

* [ ]   Not started
* [🚧]  In Progress
* [✅]   Completed

---

## 🪜 **Milestone 1XX - Core game mechanics**

### 🪜 **Milestone 101 — ECS Entity**

> *Goal: Create and destroy entities, add/remove components.*

* [✅] Implement `entity_id_t` and `entity_t` structs
* [✅] Implement `entity_create()` / `entity_destroy()` functions
* [✅] Implement set, clear and has component functions
* [✅] Implement set, clear and has flag functions
* [✅] Implement active entities list to track active entities
* [✅] Implement marked for destruction list to track entities to clean up destroy
* [✅] Implement entity cleanup function to clean up entities marked for destruction entities
* [✅] Create ECS system iteration (loop through active entities)

[✅] *End result: can create and manage entities.*

---

### 🪜 **Milestone 102 — A Map**

> *Goal: basic map.*

* [✅] Implement map. Map is a composite of map of map_terrain, entity lists and camera
* [✅] Implement map_terrain
* [✅] `map_is_walkable(x, y)` with checks for terrain

[✅] *End result: Can see the game map.*

---

### 🪜 **Milestone 103 — Renderable Entities**

> *Goal: entities can be rendered on the map.*

* [✅] Implement `renderable` component
* [✅] Render entities on the map with renderable component

[✅] *End result: Entities are rendered on the game map.*

---

### 🪜 **Milestone 104 — Entity Spawning**

> *Goal: multiple creatures and items exist on the map.*

* [✅] Implement `monster_system` to spawn monsters
* [✅] Implement `item_system` to spawn items
* [✅] Implement `feature_system` to spawn dungeon features

[✅] *End result: Can spawn monsters, items and features of different kinds*

---

### 🪜 **Milestone 105 — Player system**

> *Goal: Player can control the player entity .*

* [✅] Implement `Player` component - there can only be one player component in the game
* [✅] Implement `Player_system` and `player_update` - player can move around the map, attack enemies, pick up items, etc.

[✅] *End result: PLayer can control the player entity and interact with the game world.*

---

### 🪜 **Milestone 106 — Turn System & Timers**

> *Goal: establish turn-based logic and per-entity speed.*

* [✅] Add `Timer` component (ticks)  - implement helper functions e.g. add(), remove(), set(), reset(), and tick()
* [✅] Implement `Timer_system`, timers decrease and set fired flag when they expire
* [✅] Manage `timer`component on entity destroy
* [ ] If needed, implement timer types e.g. one_shot and recurring

[✅] *End result: Entities have one shot timer that controls their turn.*

---

### 🪜 **Milestone 107 — Movement system**

> *Goal: Entity movement mechanics.*

* [✅] Implement location component - store x and y coordinates and next entity in location list
* [✅] Implement placing an entity at a location on the map
* [✅] Implement removing an entity from the map
* [✅] Implement moving an entity on the map
* [✅] Implement `movement_system` - entities can move from one location to another
* [✅] Add player `movement` commands (arrow keys or numpad)

[✅] *End result: '@' moves around a dungeon grid.*

---

### 🪜 **Milestone 108 — Event system**

> *Goal: Systems can emit and respond to events.*

* [✅] Implement `event_system`
* [✅] Implement `event_system_emit` function to emit events

[✅] *End result: Systems can emit events that other systems respond to.*

---

### 🪜 **Milestone 109 — Containers**

> *Goal: implement container mechanic for use by chests, inventory etc.*

* [✅] Add `container` component
* [✅] Add `contained` component
* [✅] Implement `container_system`
* [✅] Implement maximum number of items in container
* [✅] Manage `container` and `contained` component cleanup on entity destroy

[✅] *End result: An entity can contain other items.*

---

### 🪜 **Milestone 110 — Inventory**

> *Goal: inventory management.*

* [✅] Add `view inventory` command
* [✅] Implement view inventory window (list container entities)
* [✅] Implement `uint8_t prompt_letter(uint8_t max_index)` input - returns the selected item or if the player cancelled

[✅] *End result: Player can view inventory and drop an item from inventory.*

---

### 🪜 **Milestone 111 — Pickup**

> *Goal: implement pickup action*

* [✅] Add player `pickup` command
* [ ] Add selection mechanic if there are multiple items on the tile
* [✅] Implement `container_try_pickup()`
* [✅] Add `event_picked_up`
* [✅] Add message log system for pick up events e.g. (“You pickup the potion.”)

[🚧] *End result: Player can pick up items.*

### 🪜 **Milestone 112 — Drop**

> *Goal: implement drop action*

* [✅] Add player `drop` command
* [✅] Add mechanic to select item to drop from inventory
* [✅] Implement `container_try_drop()`
* [✅] Add `event_dropped`
* [✅] Add message log system for drop events e.g. ("You drop the potion.")

[✅] *End result: Player can drop items.*

### 🪜 **Milestone 113 — Equipment**

> *Goal: PLayer can equip and unequip items*

* [✅] Add `equippable`, `equipped` and `slot` components
* [✅] Implement `equipment_system`
* [✅] Update view inventory window to show equipped items
* [✅] Add player `equip` command
* [✅] Add player `unequip` command
* [✅] Implement `equipment_system_try_equip()`
* [✅] Implement `equipment_system_try_unequip()`
* [✅] Add `event_item_equipped`
* [✅] Add `event_item_unequipped`
* [✅] Manage dropping equiped items
* [✅] Manage `equippable`, `equipped` and `slot` component cleanup on entity destroy
* [✅] Add message log system for equip and unequip events e.g. (“You equip the sword.”)
* [ ] Implement `equipment_system_cleanup_entity(entity)` - cleanup equipped and slots components on entity destroy

[✅] *End result: Player can equip and unequip items.*

---

### 🪜 **Milestone 114 — A Camera**

> *Goal: camera follows player as they move around the map.*

* [✅] Implement larger map
* [✅] Implement camera position and ability to pan camera
* [✅] Implement camera following player

[✅] *End result: camera follows player.*

---

### 🪜 **Milestone 115 — Implement destructible component**

> *Goal: Entities can be tageted, take damage and be destroyed*

* [✅] Implement destructible component with ac, hp, max_hp, damage_immunities, damage_resistances, damange_vulnerabilities
* [✅] Implement destructible object e.g. a creature
* [✅] Attach to destructible entities

[✅] *End result: Entities like monsters, doors, and traps can be destructible*

---

### 🪜 **Milestone 116 — Melee combat system**

> *Goal: Entities can melee combat*

* [✅] Implement `melee` component
* [✅] Implement melee weapon equipment - short sword
* [✅] Implement basic melee attack component e.g. creatures/traps
* [✅] Implement `combat system`
* [✅] Implement `combat_system_try_melee_attack()` - use equipped melee or default melee if not
* [✅] Implement `roll_melee_attack` - calculate attack roll for melee attack
* [✅] Support attack rolls by player, with or without melee weapon, and basic attack rolls (monster, trap etc)
* [✅] Implement `roll_melee_damage` - calculate damage roll for melee attack
* [✅] Support damage rolls by player, with or without melee weapon, and basic damage rolls (monster, trap etc)
* [✅] Implement `EVENT_ATTACKED` - support both hit and miss
* [✅] Add message log system for attack, damage and death events e.g. (“You hit the rat.”)
* [✅] Manage `melee` components cleanup on entity destroy

[✅] *End result: Player can equip and attack with melee weapon.*

---

### 🪜 **Milestone 117 — Damage system**

> *Goal: Entities can take damage*

* [✅] Implement `damage system`
* [✅] Implement `damage_system_try_take_damage` - apply damage to target entity
* [✅] Implement `EVENT_DAMAGED`
* [✅] Implement `damage_system_try_die` - kill an entity if it takes enough damage
* [✅] Implement `EVENT_DIED`

[✅] *End result: Entites can take damange and will die if they take enough damage*

---

### 🪜 **Milestone 118 — Damage system - immunities, resistance and vulnerabilities**

> *Goal: Objects can have damage immunities, resistances, and vulnerabilities*

* [✅] Create an object with an immunity / resistance / vulnerability to a specific damage type
* [✅] Update `damage_system` to take immunities into account
* [✅] Update `damage_system` to take resistances into account
* [✅] Update `damage_system` to take vulnerabilities into account

[✅] *End result: Damage calculation takes objects immunities, resistances and vulnerabilities into account.*

---

### 🪜 **Milestone 119 — Stats system**

> *Goal: Entities can have stats e.g. STR, DEX etc.*

* [✅] Implement `Stats` component
* [🚧] Implement `Stats_system`

[🚧] *End result: Stats takes active effects into account.*

---

### 🪜 **Milestone 120 — Targetting mode and line of sight**

> *Goal: entities can target.*

* [✅] Add targetting mode - supporting differrent target types tile/entity etc, if line of sight is required, maximum distance, etc.
* [✅] Add player `look` command (examine tile/entity)
* [✅] Implement player target selection input
* [✅] Implement line of sight test
* [✅] Implement `player_try_look()`

[✅] *End result: Player can target a tile and examine a tile/entity if in line of sight.*

---

### 🪜 **Milestone 121 — Ranged combat**

> *Goal: entities can range attack.*

* [✅] Implement `ranged` attack component
* [✅] Implement ranged weapon equipment
* [✅] Implement basic ranged attack component e.g. creatures / traps
* [✅] Add player `target` command (ranged attack)
* [✅] Update combat system to support ranged attacks

[✅] *End result: You can range attack and kill monsters.*

---

### 🪜 **Milestone 121b — Ammo**

> *Goal: Ammo.*

* [✅] Implement `ammo` component
* [✅] Update `ranged` attack component to implement `allowed_ammo`
* [✅] Update `item_system` to support `allowed_ammo`
* [✅] Update `item_system` to support ammo items
* [✅] Update combat system to support ranged ammo
* [✅] Implement a generic `consume` item or destroy function

[✅] *End result: Ranged attacks can use ammo.*

### 🪜 **Milestone 122 — Experience**

> *Goal: Player gains experience.*

* [ ] Implement experience component that gives experience
* [ ] Implement experience system to track player's experience
* [ ] Implement player experience
* [ ] Implement gain experience

[ ] *End result: player gains experience.*

---

### 🪜 **Milestone 123 — Player Levels**

> *Goal: Player can level up.*

* [ ] Implement player levels
* [ ] Implement player levelling up

[ ] *End result: player can level up.*

---

### 🪜 **Milestone 124 — Instant effects**

> *Goal: entities can have instant effects.*

* [✅] Implement `effect_t` that describes an event that could happen - type, magnitude, duration (0 = instant), stat, status
* [✅] Implement `effect_kind_t` enum e.g. EFFECT_DAMAGE, EFFECT_HEAL
* [✅] Implement `ATTRIBUTE_t` enum e.g. ATTRIBUTE_CUR_HP
* [✅] Implement `effect_system`
* [✅] Implement `effect_system_handle_event()` - create effect triggers based on game events
* [✅] Implement `process_trigger()` - process triggers and apply effects
* [✅] Implement `apply_effect()` - apply an effect e.g. heal, damage etc

[✅] *End result: Entities can apply instant effects e.g. when food is consumed, potion quaffed etc.*

---

### 🪜 **Milestone 125 — Active effects**

> *Goal: Entities can have active effects that last for a period of time or are permanant.*

* [✅] Implement `active effect` - details of an active effect - an effect_t and source
* [✅] Implement `ATTRIBUTE_t` that details target type e.g. cur_hp, max_hp, cur_mp, max_mp etc.
* [✅] Implement `active effects` component - an array of active_effect[MAX_EFFECTS]
* [ ] Implement `status_flags_t` flags e.g. poisoned
* [✅] Extend `effect_kind_t` enum with EFFECT_STAT_MODIFIER (+/- stat while active)
* [✅] Place active effects in system banked memory as only ever access via system and large in size
* [✅] Extend `apply_effects_by_source(actor, item)` to handle applying active effects to the actor
* [✅] Implement `effect_system_process_entity_turn(actor)` to handle duration active effects. Remove effects when duration expires
* [✅] Implement `remove_effects_by_source(actor, source)` - handle removing active effects of the source item from the actor
* [✅] Implement `active_effects_sum_mod` to calculate and return the sum of the modifiers applied to a target
* [✅] Respond to unequip events and  remove effects when source is unequipped (e.g. unequipped weapon)
* [✅] Implement active effect cleanup on entity destruction. If source has effect component, scan all entities for active effects for that source and remove the effect.

[🚧] *End result: stats and status are affected by active effect.*

### 🪜 **Milestone 126 — Implement steppable entities**

> *Goal: Entities can react to being stood on*

* [ ] Add `Steppable` component with step_effect and single_use
* [ ] Add `EVENT_STOOD_ON` event
* [ ] Update movement system to check for entities at entered location and emit an `EVENT_STOOD_ON` for each
* [ ] Implement steppable_system
* [ ] Implement `steppable_system_on_stood_on()`to handle events e.g. check for steppable component and take action
* [ ] Implement trap feature
* [ ] Add message log system for stood on events e.g. (“You stood on the trap.”)
* [ ] Remove steppable components on entity destroy

[ ] *End result: Traps react to being stood on*

---

### 🪜 **Milestone 127 — Implement bumpable entities**

> *Goal: Entities can react to being bumped into.*

* [ ] Add `Bumpable` component with `bump_action`
* [ ] Update movement system to emit `EVENT_BUMPED` when a move is blocked by a bumpable entity
* [ ] Implement `bumpable_system` and `bumpable_system_on_bumped()`
* [ ] Implement unlocked door as bumpable (opens on bump)
* [ ] Remove bumpable component on entity destroy

[ ] *End result: Unlocked doors open if you walk into them*

---

### 🪜 **Milestone 128 — Field of View & Exploration Tracking**

> *Goal: Player can only see within their field of view; explored tiles are remembered.*

* [ ] Add per-tile `explored` flag to map (persists after leaving FOV)
* [ ] Implement FOV computation (e.g. shadowcasting) stored as per-tile `visible` flag
* [ ] Recompute FOV each turn when player moves
* [ ] Update renderer: only draw tiles that are explored; dim tiles outside current FOV
* [ ] Update monster AI: monsters only spot player if player is within FOV

[ ] *End result: Player explores the dungeon with limited visibility; monsters cannot see through walls.*

---

### 🪜 **Milestone 129 — Natural regeneration**

> *Goal: Entities regenerate HP slowly over time when not in combat.*

* [ ] Add `regen_rate` field to `destructible_comp` (turns between +1 HP ticks; 0 = no regen)
* [ ] Implement regen tick in turn system: every `regen_rate` turns, heal 1 HP if below max
* [ ] Emit `EVENT_HEALED_HP` on regen tick (message log already handles this event)
* [ ] Set player regen rate; monsters do not regenerate by default

[ ] *End result: Player recovers HP slowly by waiting; creates incentive to rest between fights.*

---

### 🪜 **Milestone 130 — Status effects**

> *Goal: Entities can be poisoned, paralysed, or confused; status affects their turn.*

* [ ] Implement `status_flags_t` bitmask: `STATUS_POISONED`, `STATUS_PARALYSED`, `STATUS_CONFUSED`
* [ ] Add status fields to `destructible_comp`: `status_flags_t status` and `uint8_t status_duration`
* [ ] Implement `status_system` — process status flags each entity turn
* [ ] Poison — deal 1 HP damage per turn for duration; emit `EVENT_DAMAGED`
* [ ] Paralysis — skip entity turn for duration
* [ ] Confusion — randomise movement direction for duration
* [ ] Implement `status_system_apply(entity, status, duration)` and `status_system_clear(entity, status)`
* [ ] Display active status icons on player status UI (Milestone 602)
* [ ] Remove status on entity destroy

[ ] *End result: Monsters can poison, paralyse, or confuse the player; status creates tactical urgency.*

---

### 🪜 **Milestone 199 — Cleanup & bugs**

> *Goal: Cleanup code*

* [ ] Turn item component into a flag to indicate can be picked up (consider renaming)
* [ ] Change player in to character component and use for character specific things like experience
* [ ] Change pass by value to pass by pointer if parameter is on stack or in global game state
* [ ] Bug - attack direction can select no direction and attack self
* [ ] Bug - speed - show as (20 - speed) in UI so faster is a higher number. Need to clamp speed to max

[ ] *End result: Code is clean and known bugs are fixed.*

---

## 🪜 **Milestone 2XX — Items**

### 🪜 **Milestone 201 — Melee weapons**

> *Goal: Variety of melee weapons*

* [ ] Implement dagger (fast, low damage)
* [ ] Implement short sword (balanced)
* [ ] Implement longsword (slow, high damage)
* [ ] Implement club / mace (blunt damage type)
* [ ] Register all items in item factory

[ ] *End result: Game should have a variety of melee weapons.*

---

### 🪜 **Milestone 202 — Ranged weapons**

> *Goal: Variety of ranged weapons*

* [ ] Implement short bow (uses arrows)
* [ ] Implement crossbow (uses bolts, slower but higher damage)
* [ ] Implement sling (uses stones)
* [ ] Register all items in item factory

[ ] *End result: Game should have a variety of ranged weapons.*

---

### 🪜 **Milestone 203 — Armour**

> *Goal: Variety of armour*

* [ ] Implement leather armour (light, low AC)
* [ ] Implement chain mail (medium AC)
* [ ] Implement plate armour (high AC, speed penalty)
* [ ] Register all items in item factory

[ ] *End result: Game should have a variety of armour.*

---

### 🪜 **Milestone 204 — Shields**

> *Goal: Variety of shields*

* [ ] Implement small shield (low AC bonus)
* [ ] Implement large shield (higher AC bonus, speed penalty)
* [ ] Register all items in item factory

[ ] *End result: Game should have a variety of shields.*

---

### 🪜 **Milestone 205 — Ammo**

> *Goal: Variety of ammo*

* [ ] Implement arrows (for short bow)
* [ ] Implement bolts (for crossbow)
* [ ] Implement stones (for sling)
* [ ] Register all items in item factory

[ ] *End result: Game should have a variety of ammo.*

---

### 🪜 **Milestone 206 — Potions**

> *Goal: PLayer can quaff potions*

* [ ] Implement a potion e.g. potion of healing
* [ ] Implement a variety of potions
* [ ] Add player `quaff` command - select from inventory
* [ ] Implement `consumable_system_try_quaff`
* [ ] Add message log system for potion quaffed events e.g. (“You quaff the potion of healing.”)

[ ] *End result: Potion is destroyed and any effect applied.*

---

### 🪜 **Milestone 207 — Scrolls**

> *Goal: PLayer read scrolls*

* [ ] Implement a scroll e.g. potion of teleportation
* [ ] Implement a variety of scrolls
* [ ] Add player `read` command - select from inventory
* [ ] Implement `magic_system_try_readf`
* [ ] Add message log system for reading scroll effects e.g. (“You read the scroll.”)

[ ] *End result: Scroll is destroyed and any magic spell cast.*

---

### 🪜 **Milestone 208 — Consumables**

> *Goal: eat food to restore health.*

* [ ] Implement `consumable` component with `consumable_method_t` e.g.eat, quaffe, drink, etc.
* [ ] Implement a consumable e.g. bread
* [ ] Implement a variety of consumables
* [ ] Add player `eat` command - select from inventory
* [ ] Implement `consumption_system`
* [ ] Implement `consumption_system_try_eat()`. Handle eating food including decrement or destroy, emitting `effect` events and `consumed` event
* [ ] Trigger applying effects to actor
* [ ] Implement `item_decrement_or_destroy`
* [ ] Add message log system for food `consumed` events e.g. (“You eat the apple.”)

[ ] *End result: Player can restore health by eating food and food is destroyed.*

---

### 🪜 **Milestone 209 — Wands**

> *Goal: PLayer zap wands*

* [ ] Implement a wand
* [ ] Implement a variety of wands
* [ ] Add player `zap` command - select from inventory
* [ ] Implement `magic_system_try_zap`
* [ ] Add message log system for zap effects e.g. (“You zap the wand of fire.”)

[ ] *End result: Zap charge is used and any magic spell cast.*

---

### 🪜 **Milestone 210 — Keys**

> *Goal: Openable items can be locked with keys*

* [ ] Implement a key
* [ ] Implement a variety of keys
* [ ] Add player `unlock` command - select from inventory
* [ ] Implement `lock_system_try_unlock`
* [ ] Add message log system for unlock effects e.g. (“You unlock the door.”)

[ ] *End result: Lockable entity can be unlocked.*

---

### 🪜 **Milestone 211 — Gold and currency**

> *Goal: Gold exists as a collectible resource; player score is tracked.*

* [ ] Add `gold` field (uint16_t) to player state
* [ ] Implement gold pile as a map entity: auto-picked up on step, not stored in inventory
* [ ] Dungeon generator places gold piles scaled by depth
* [ ] Display gold count on status UI
* [ ] Use gold total as the base for death-screen score (score = depth × gold)

[ ] *End result: Player collects gold; gold drives the death-screen score.*

---

### 🪜 **Milestone 212 — Item stacking**

> *Goal: Identical items stack in inventory, saving slots.*

* [ ] Add `stack_count` field (uint8_t) to item component
* [ ] On pickup: if identical item already in inventory, increment count instead of adding a slot
* [ ] On drop: decrement count; remove slot when count reaches 0 (reuse `item_decrement_or_destroy`)
* [ ] Update inventory window to display count (e.g. "3 × healing potion")
* [ ] Ammo items stack by default

[ ] *End result: Arrows, potions, and scrolls of the same type share one inventory slot.*

---

### 🪜 **Milestone 213 — Item identification**

> *Goal: Potions, scrolls, and wands start unidentified; the player learns what they are by using them.*

* [ ] Add `identified` flag to item component
* [ ] Add per-run appearance table: randomised name mapped to true item type (e.g. "pink potion" → healing potion)
* [ ] Render unidentified items using randomised appearance name; render identified items using true name
* [ ] On use: mark item type as identified for the rest of the run
* [ ] Implement `scroll of identify` — player selects an item from inventory to identify
* [ ] Add message log for identification e.g. ("The pink potion was a potion of healing!")

[ ] *End result: Items are mysterious on first encounter; knowledge accumulates across a run.*

---

## 🪜 **Milestone 3XX — Monster AI**

### 🪜 **Milestone 301 — Basic Monster AI System**

> *Goal: monsters can act intelligently.*

* [✅] Implement `AI` component - implement helper functions e.g. add() and remove()
* [✅] Implement `AI system`
* [✅] Define `ai_state_t`
* [✅] Implement `ai_on_event()` to process events and transition between states
* [✅] Add `ai_system_process_entity_turn()` - entity takes it turn

[✅] *End result: AI framework.*

---

### 🪜 **Milestone 302 — Sleep state**

> *Goal: monsters can sleep.*

* [✅] Implement `sleep()` - monster does nothing
* [ ] Implement chance of waking up

[🚧] *End result: Monsters can sleep.*

---

### 🪜 **Milestone 303 — Wandering state**

> *Goal: monsters can wander.*

* [✅] Implement `wander()` - monster performs 'drunk' walk

[✅] *End result: Monsters can drunken walk.*

---

### 🪜 **Milestone 304 — Attack state**

> *Goal: monsters can attack.*

* [✅] Implement `attack_target()` - perform melee attacks
* [ ] Extend - to support ranged attacks

[🚧] *End result: Monsters can attack.*

---

### 🪜 **Milestone 305 — Track state**

> *Goal: monsters will track target when not visible.*

* [✅] Implement `track_target()` - monster will move to last known position of target

[✅] *End result: Monsters move to the last known position of their target.*

---

### 🪜 **Milestone 306 — Search state**

> *Goal: monsters will search target when not visible.*

* [✅] Implement `search_target()` - monster will search to reaquire target

[✅] *End result: Monsters can reacquire target.*

---

### 🪜 **Milestone 307 — Flee state**

> *Goal: monsters will flee.*

* [✅] Implement `flee()` - monster will flee

[✅] *End result: Monsters can flee.*

---

### 🪜 **Milestone 308 — Monster definitions**

> *Goal: A variety of monsters exist with different stats, speeds, and behaviours.*

* [ ] Define monster data table (name, tile, hp, ac, speed, melee attack, XP value, AI flags)
* [ ] Implement rat / basic melee monster
* [ ] Implement archer / basic ranged monster
* [ ] Implement fast monster (high speed)
* [ ] Implement tough monster (high hp/ac)
* [ ] Update dungeon generator to place monster variety per depth

[ ] *End result: Multiple distinct monster types populate the dungeon.*

---

## 🪜 **Milestone 4XX — Features**

### 🪜 **Milestone 401 — Dungeon features and basic doors**

> *Goal: dungeons can have features that can be interacted with.*

* [✅] Implement feature factory to spawn features
* [✅] Implement openable component
* [✅] Implement a basic door feature
* [✅] Add player `open` command for doors
* [✅] Add player `close` command for doors
* [✅] Implement `try_open_door()` for door
* [✅] Implement `try_close_door()` for door
* [✅] Add `event_door_opened`
* [✅] Add `event_door_closed`
* [✅] Prevent walking through closed doors
* [✅] Destroy feature component on entity destroy
* [🚧] Add message log system for open/close door events e.g. (“You open the door.”)

[🚧] *End result: Player can open and close basic doors.*

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

* [✅] Implement up and down stair features
* [✅] Add player `climb` command for stairs
* [✅] Implement `try_climb()` for stairs
* [✅] Add `transition_comp` for entities that can cause transition events e.g. stairs, pits, etc
* [✅] Implement `EVENT_TRANSITION` to trigger transition to a different depth e.g. transition_up (stairs), transition_down (stairs), transition_fall (pit), transition_teleport (new game, magic)
* [✅] Implement `transition system` for transitioning depth levels
* [ ] Add message log system for stair events e.g. ("You descend the stairs.")

[🚧] *End result: Player can ascend and descend stairs to change depth.*

---

### 🪜 **Milestone 404 — Shops**

> *Goal: The player can buy and sell items at a shop.*

* [ ] Implement `vendor` component with stock list and price table
* [ ] Implement shop as a dungeon feature (spawned by generator on some levels)
* [ ] Add player `buy` command — opens shop inventory UI; deducts gold
* [ ] Add player `sell` command — sells selected inventory item; adds gold
* [ ] Implement `shop_system_try_buy()` and `shop_system_try_sell()`
* [ ] Add message log for transactions e.g. ("You buy the potion of healing for 50 gold.")

[ ] *End result: Player can spend collected gold on items; gold becomes a meaningful resource.*

---

## 🪜 **Milestone 5XX — Dungeon Generation & Progression**

### 🪜 **Milestone 501 — Dungeon Generation**

> *Goal: procedural dungeon generator.*

* [✅] Implement procedural map generator (rooms + corridors)
* [🚧] Place stairs up/down
* [✅] Place player
* [🚧] Place new monsters, taking depth into account
* [🚧] Place new items, taking depth into account
* [ ] Place persistent items that are at the current depth
* [🚧] Add new features, taking depth into account
* [ ] Place basic doors
* [ ] Place locked doors and keys
* [ ] Place other feature types
* [ ] Implement dungeon map decoration

[ ] *End result: Dungeon with rooms, corridors and populated with entities.*

---

### 🪜 **Milestone 502 — Dungeon level transition**

> *Goal: handle depth transitions (load next map).*

* [🚧] Implement persistent entities with an associated depth
* [✅] Implement persistance entity check (recursive)
* [✅] Implement deletion of non persistent entities
* [✅] Implement depth change including moving player to new depth
* [✅] Update map generator to place persitent entities on level
* [✅] Call map generator

[ ] *End result: Able to transition levels and persistent entities are retained.*

---

## 🪜 **Milestone 6XX — UI, Messages & Status**

### 🪜 **Milestone 601 — Message log UI**

> *Goal: Display messages in response to game events.*

* [✅] Implement message log window
* [ ] Implement 'press key to continue' if messages exceeds window size before players next turn

[🚧] *End result: Player is notified of game events.*

### 🪜 **Milestone 602 — Status UI**

> *Goal: Display player status.*

* [✅] Display player primary stats (Strength, dexterity etc)
* [✅] Update primary stats on change (e.g. equip, unequip, levelup, attach/unattach effect etc)
* [✅] Display player secondary stats (Speed etc)
* [✅] Update secondary stats on change (e.g. equip, unequip, levelup, effect? etc)
* [✅] Display player resource stats (Max HP, Cur HP etc)
* [✅] Update resource stats on change (e.g. damage, equip, unequip, levelup, attach/unattach effect etc)
* [ ] Display player status (posioned etc)
* [ ] Update status on change (e.g. poisoned)

[🚧] *End result: Player can see current status.*

### 🪜 **Milestone 603 — Game modes & context-sensitive hint bar**

> *Goal: Game loop is driven by a mode state machine; a hint bar displays available keys for the current mode.*

* [ ] Add `game_mode_t` enum: `MODE_PLAYER_TURN`, `MODE_TARGETING`, `MODE_MENU`
* [ ] Refactor main game loop to dispatch input via current `game_mode_t`
* [ ] Implement hint bar UI widget (single line, shows key legend)
* [ ] Player turn mode — hint bar shows movement, action, and shortcut keys
* [ ] Targeting mode — hint bar shows "Move target: arrows  Confirm: T  Cancel: Esc"
* [ ] Menu mode — hint bar shows relevant menu navigation keys

[ ] *End result: Player always sees relevant key hints; new modes can be added by extending the enum and handler table.*

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

### 🪜 **Milestone 701 — Game data structure verification**

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
* [ ] Projectile visual effects (bolts, arrows in flight)
* [ ] Spellcasting system
* [ ] Equipment and inventory weights
* [ ] Procedural names/descriptions
* [ ] Multiple dungeon themes

---
