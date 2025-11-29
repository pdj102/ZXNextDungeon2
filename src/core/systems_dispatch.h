/**
 * @file systems_dispatch.h
 * @author Paul Johnson
 * @brief Game SYSTEMS_DISPATCH
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SYSTEMS_DISPATCH_H
#define SYSTEMS_DISPATCH_H

#include <stdint.h>

#include "../ecs/entity.h"
#include "../ecs/components/item_comp.h"
#include "../ecs/components/creature_comp.h"
#include "../ecs/systems/PAGE42/event_system.h"

#include "text.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

/* Actions System */
bool_t system_actions_try_melee_attack(entity_id_t creature, entity_id_t target);
bool_t system_actions_try_pickup(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_drop(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_quaff(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_eat(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_equip(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_unequip(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_open(entity_id_t creature, entity_id_t feature);
bool_t system_actions_try_close(entity_id_t creature, entity_id_t feature);
int8_t system_actions_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type);
bool_t system_actions_try_die(entity_id_t creature);
bool_t system_actions_try_move(entity_id_t entity, int8_t dx, int8_t dy);

/* Container System*/
void system_container_init(void);
bool_t system_container_place_item_in(entity_id_t container, entity_id_t item);
void system_container_remove_item_from(entity_id_t container, entity_id_t item);
uint8_t system_container_count(entity_id_t container);
entity_id_t system_container_get_first(entity_id_t container);
entity_id_t system_container_get_next(entity_id_t entity);
entity_id_t system_container_get_at(entity_id_t container, uint8_t position);
void system_container_mark_contents_for_destruction(entity_id_t container);
void system_container_clean_up(void);

/* Equipment system*/
void system_equipment_init(void);
entity_id_t system_equipment_create(item_kind_t kind, uint8_t quantity);
void system_equipment_print_name(text_window_t *win, item_kind_t kind);
void system_equipment_get_tile(entity_id_t id, zxnext_tile_t *tile);

/* Event System */
void system_event_init(void);
void system_event_emit(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val);

/* Monster system*/
void system_monster_init(void);
entity_id_t system_monster_create(creature_kind_t kind);
entity_id_t system_monster_create_player( void );
void system_monster_print_name(text_window_t *win, creature_kind_t kind);
void system_monster_get_tile(entity_id_t id, zxnext_tile_t *tile);

/* Player System */
void system_player_init(void);
void system_player_update(void);

/* Timer System */
void system_timer_init(void);
void system_timer_update(void);






#endif // SYSTEMS_DISPATCH_H