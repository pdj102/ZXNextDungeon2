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
#include "ecs/components/creature_comp.h"
#include "ecs/components/name_comp.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/stats_comp.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/destructible_comp.h"

#include "ecs/systems/PAGE32/item_system.h"
#include "ecs/systems/PAGE42/event_system.h"
#include "ecs/systems/PAGE72/feature_system.h"

#include "game/spatial.h"

#include "core/text.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void systems_init(void);

/* AI System */
void system_ai_handle_event(const event_t *event);
void system_ai_process_entity_turn(entity_id_t id);

/* Actions System */
void system_actions_init(void);
bool system_actions_try_melee_attack(entity_id_t creature, entity_id_t target);
bool system_actions_try_pickup(entity_id_t creature, entity_id_t item);
bool system_actions_try_drop(entity_id_t creature, entity_id_t item);
bool system_actions_try_quaff(entity_id_t creature, entity_id_t item);
bool system_actions_try_eat(entity_id_t creature, entity_id_t item);
bool system_actions_try_equip(entity_id_t creature, entity_id_t item);
bool system_actions_try_unequip(entity_id_t creature, entity_id_t item);
bool system_actions_try_open(entity_id_t creature, entity_id_t feature);
bool system_actions_try_close(entity_id_t creature, entity_id_t feature);

/* Consumable System*/
void system_consumable_init(void);
bool system_consumable_try_consume(entity_id_t actor, entity_id_t entity);

/* Container System*/
void system_container_init(void);
bool system_container_try_pickup(entity_id_t container, entity_id_t item);
bool system_container_try_drop(entity_id_t container, entity_id_t item);
void system_container_add(entity_id_t container, entity_id_t item);
void system_container_remove(entity_id_t item);
uint8_t system_container_count(entity_id_t container);
entity_id_t system_container_get_first(entity_id_t container);
entity_id_t system_container_get_next(entity_id_t entity);
entity_id_t system_container_get_at(entity_id_t container, uint8_t position);
void system_container_mark_contents_for_destruction(entity_id_t container);
void system_container_clean_up(entity_id_t id);
bool system_container_is_protected_by_persistence(entity_id_t id);

/* Combat system */
void system_combat_init(void);
bool system_combat_try_attack(entity_id_t creature, entity_id_t target, attack_kind_t kind);
uint8_t system_combat_attack_range(entity_id_t attacker, attack_kind_t kind);

/* Damage system */
void system_damage_init(void);
int8_t system_damage_try_take_damage(entity_id_t creature, int8_t damage, damage_flag_t flag);
bool system_damage_try_die(entity_id_t creature);

/* Door system*/
bool system_door_try_open(entity_id_t actor, entity_id_t entity);
bool system_door_try_close(entity_id_t actor, entity_id_t entity);

/* Item system*/
entity_id_t system_item_create(item_kind_t kind, uint8_t quantity);

/* Effect system */
void system_effect_init(void);
void system_effect_handle_event(const event_t *event);
void system_effect_process_entity_turn(entity_id_t entity);
void system_effect_cleanup_entity(entity_id_t source);
int8_t system_effect_mod_sum(entity_id_t actor, attribute_t attribute);

/* Event System */
void system_event_init(void);
void system_event_emit(const event_t *event);


/* Equipment System */
void system_equipment_init(void);
bool system_equipment_try_equip(entity_id_t actor, entity_id_t item);
bool system_equipment_try_unequip(entity_id_t actor, entity_id_t item);
bool system_equipment_is_equipped(entity_id_t actor, entity_id_t item);
void system_equipment_cleanup(entity_id_t id);

/* Feature system*/
void system_feature_init(void);
entity_id_t system_feature_create(feature_kind_t kind);

/* Healing System*/
int8_t system_healing_try_take_healing(entity_id_t creature, int8_t amount, healing_kind_t kind);

/* Monster system*/
void system_monster_init(void);
entity_id_t system_monster_create(creature_kind_t kind);
entity_id_t system_monster_create_player( void );

/* Movement system */
void system_movement_init(void);
void system_movement_place(entity_id_t actor, uint8_t x, uint8_t y);
bool system_movement_try_move(entity_id_t actor, int8_t dx, int8_t dy);
bool system_movement_try_move_random(entity_id_t actor);
bool system_movement_try_move_towards(entity_id_t entity, coord_t *coord);
bool system_movement_location_equal(entity_id_t entity1, entity_id_t entity2);
bool system_movement_are_adjacent(entity_id_t entity1, entity_id_t entity2);
void system_movement_detach(entity_id_t id);

/* Name system */
void system_name_print(text_window_t *win, name_id_t name);

/* Perception system*/
bool system_perception_try_check(entity_id_t creature);
bool system_perception_can_see_target(entity_id_t ai, entity_id_t target);

/* Player System */
void system_player_init(void);
void system_player_update(void);

/* Stats system */
void system_stats_init(void);
uint8_t system_stats_get_stat_cur(entity_id_t actor, stat_kind_t stat);
uint8_t system_stats_get_stat_base(entity_id_t actor, stat_kind_t stat);
int8_t system_stats_get_stat_modifier(entity_id_t actor, stat_kind_t stat);
uint8_t system_stats_get_speed_cur(entity_id_t actor);
uint8_t system_stats_get_speed_base(entity_id_t actor);
uint8_t system_stats_get_ac_cur(entity_id_t actor);
uint8_t system_stats_get_ac_base(entity_id_t actor);
uint8_t system_stats_get_hp_cur(entity_id_t actor);
uint8_t system_stats_get_hp_max(entity_id_t actor);

/* Timer System */
void system_timer_init(void);
void system_timer_update(void);
bool system_timer_has_fired(entity_id_t entity);
void system_timer_reset(entity_id_t entity);
void system_timer_start(entity_id_t entity);
void system_timer_stop(entity_id_t entity);
void system_timer_cleanup(entity_id_t entity);

/* Transition System */
void system_transition_try(entity_id_t source, entity_id_t target);

#endif // SYSTEMS_DISPATCH_H