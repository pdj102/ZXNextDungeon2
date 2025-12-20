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

#include "ecs/entity.h"
#include "ecs/components/PAGE50/item_comp.h"
#include "ecs/components/PAGE50/creature_comp.h"
#include "ecs/components/PAGE50/name_comp.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "game/game.h"

#include "core/text.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void systems_init(void);

/* Actions System */
void system_actions_init(void);
bool_t system_actions_try_melee_attack(entity_id_t creature, entity_id_t target);
bool_t system_actions_try_pickup(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_drop(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_quaff(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_eat(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_equip(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_unequip(entity_id_t creature, entity_id_t item);
bool_t system_actions_try_open(entity_id_t creature, entity_id_t feature);
bool_t system_actions_try_close(entity_id_t creature, entity_id_t feature);

/* Consumable System*/
void system_consumable_init(void);
bool_t system_consumable_try_consume(entity_id_t actor, entity_id_t entity);

/* Container System*/
void system_container_init(void);
bool_t system_container_try_pickup(entity_id_t container, entity_id_t item);
bool_t system_container_try_drop(entity_id_t container, entity_id_t item);
void system_container_add(entity_id_t container, entity_id_t item);
void system_container_remove(entity_id_t container, entity_id_t item);
uint8_t system_container_count(entity_id_t container);
entity_id_t system_container_get_first(entity_id_t container);
entity_id_t system_container_get_next(entity_id_t entity);
entity_id_t system_container_get_at(entity_id_t container, uint8_t position);
void system_container_mark_contents_for_destruction(entity_id_t container);
void system_container_clean_up(entity_id_t id);

/* Combat system */
void system_combat_init(void);
bool_t system_combat_try_melee_attack(entity_id_t creature, entity_id_t target);

/* Damage system */
void system_damage_init(void);
int8_t system_damage_try_take_damage(entity_id_t creature, int8_t damage, damage_kind_t kind);
bool_t system_damage_try_die(entity_id_t creature);

/* Item system*/
void system_item_init(void);
entity_id_t system_item_create(item_kind_t kind, uint8_t quantity);

/* Effect system */
void system_effect_init(void);
void system_effect_handle_event(const event_t event);

/* Event System */
void system_event_init(void);
void system_event_emit(const event_t event);

/* Equipment System */
void system_equipment_init(void);
bool_t system_equipment_try_equip(entity_id_t actor, entity_id_t item);
bool_t system_equipment_try_unequip(entity_id_t actor, entity_id_t item);
bool_t system_equipment_is_equipped(entity_id_t actor, entity_id_t item);
void system_equipment_clean_up(entity_id_t id);

/* Monster system*/
void system_monster_init(void);
entity_id_t system_monster_create(creature_kind_t kind);
entity_id_t system_monster_create_player( void );

/* Movement system */
void system_movement_init(void);
bool_t system_movement_try_move(entity_id_t actor, int8_t dx, int8_t dy);
bool_t system_movement_location_equal(entity_id_t entity1, entity_id_t entity2);

/* Name system */
void system_name_print(text_window_t *win, name_id_t name);

/* Player System */
void system_player_init(void);
void system_player_update(void);

/* Stats system */
void system_stats_init(void);
uint8_t system_stats_get_stat(entity_id_t actor, stat_type_t stat);
int8_t system_stats_get_stat_mod(entity_id_t actor, stat_type_t stat);
speed_t system_stats_get_speed(entity_id_t actor);

/* Timer System */
void system_timer_init(void);
void system_timer_update(void);
bool_t system_timer_has_fired(entity_id_t entity);
void system_timer_reset(entity_id_t entity);

#endif // SYSTEMS_DISPATCH_H