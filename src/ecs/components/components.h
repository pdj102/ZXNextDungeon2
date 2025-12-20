/**
 * @file components.h
 * @author Paul Johnson
 * @brief 
 */

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdint.h>

#include "ecs/components/PAGE50/attack_comp.h"
#include "ecs/components/PAGE50/creature_comp.h"
#include "ecs/components/PAGE50/consumable_comp.h"
#include "ecs/components/PAGE50/destructible_comp.h"
#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/equippable_comp.h"
#include "ecs/components/PAGE50/item_comp.h"
#include "ecs/components/PAGE50/name_comp.h"

#include "ecs/components/PAGE51/stats_comp.h"

#include "ecs/entity.h"

#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void components_init(void);

/* attack */
void comp_melee_add(entity_id_t entity, const attack_comp_t melee);
void comp_ranged_add(entity_id_t entity, const attack_comp_t attack);
void comp_melee_remove(entity_id_t entity);
void comp_ranged_remove(entity_id_t entity);

/* consuamble */
void comp_consumable_add(entity_id_t entity);
void comp_consumable_remove(entity_id_t entity);

/* contained */
void comp_contained_add(entity_id_t entity, entity_id_t container, entity_id_t next);
void comp_contained_remove(entity_id_t entity);

/* container */
void comp_container_add(entity_id_t entity);
void comp_container_remove(entity_id_t entity);

/* creature */
void comp_creature_add(entity_id_t entity, creature_kind_t kind);
void comp_creature_remove(entity_id_t entity);

/* destructible */
void comp_destructible_add(entity_id_t entity, const destructible_comp_t destructible);
void comp_destructible_remove(entity_id_t entity);

/* equippable */
void comp_equippable_add(entity_id_t entity, equippable_slot_t type);
void comp_equippable_remove(entity_id_t entity);

/* equipped */
void comp_equipped_add(entity_id_t entity, entity_id_t equipped_by);
void comp_equipped_remove(entity_id_t entity);

/* effect */
void comp_effect_add(entity_id_t entity, effect_comp_t effect);
void comp_effect_remove(entity_id_t entity);

/* item */
void comp_item_add(entity_id_t entity, item_kind_t type, uint8_t quantity);
void comp_item_remove(entity_id_t entity);

/* location */
void comp_location_init(void);
void comp_location_add(entity_id_t entity, uint8_t x, uint8_t y);
void comp_location_move(entity_id_t entity, uint8_t x, uint8_t y);
void comp_location_remove(entity_id_t entity);

/* name */
void comp_name_add(entity_id_t entity, name_id_t name);
void comp_name_remove(entity_id_t entity);
void system_name_print(text_window_t *win, name_id_t name);

/* player */
void comp_player_add(entity_id_t entity);
void comp_player_remove(entity_id_t entity);

/* renderable */
void comp_renderable_add(entity_id_t entity, const zxnext_tile_t tile);
void comp_renderable_remove(entity_id_t entity);

/* slots */
void comp_slots_add(entity_id_t entity);
void comp_slots_remove(entity_id_t entity);

/* stats */
void comp_stats_add(entity_id_t entity, const stats_comp_t stats_p);
void comp_stats_remove(entity_id_t entity);

/* timer */
void comp_timer_init(void);
void comp_timer_add(entity_id_t entity, ticks_t ticks);
void comp_timer_remove(entity_id_t entity);

#endif // COMPONENTS_H
