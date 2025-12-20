/**
 * @file healing_system.h
 * @author Paul Johnson
 * @brief healing system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HEALING_SYSTEM_H
#define HEALING_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/game.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
int8_t healing_system_try_take_healing(entity_id_t creature, int8_t healing, healing_type_t type);
bool_t healing_system_try_die(entity_id_t creature);

#endif // HEALING_SYSTEM_H
