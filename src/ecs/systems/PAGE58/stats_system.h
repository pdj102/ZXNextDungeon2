/**
 * @file stats_system.h
 * @author Paul Johnson
 * @brief stats system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef STATS_SYSTEM_H
#define STATS_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/stats_comp.h"

#include "game/game.h"

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/

/* primary stats */
uint8_t stats_system_get_stat_cur(entity_id_t actor, stat_type_t stat);
uint8_t stats_system_get_stat_base(entity_id_t actor, stat_type_t stat);
int8_t stats_system_get_stat_modifier(entity_id_t actor, stat_type_t stat);

/* secondary stats */
uint8_t stats_system_get_speed_cur(entity_id_t actor);
uint8_t stats_system_get_speed_base(entity_id_t actor);
uint8_t stats_system_get_ac_cur(entity_id_t actor);
uint8_t stats_system_get_ac_base(entity_id_t actor);

/* resource stats */
uint8_t stats_system_get_hp_cur(entity_id_t actor);
uint8_t stats_system_get_hp_max(entity_id_t actor);

#endif // STATS_SYSTEM_H
