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

#include "game/game.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
uint8_t stats_system_get_stat(entity_id_t actor, stat_type_t stat);
int8_t stats_system_get_stat_mod(entity_id_t actor, stat_type_t stat);
speed_t stats_system_get_speed(entity_id_t actor);

#endif // STATS_SYSTEM_H
