/**
 * @file damage_system.h
 * @author Paul Johnson
 * @brief damage system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DAMAGE_SYSTEM_H
#define DAMAGE_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
int8_t damage_system_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type);
bool_t damage_system_try_die(entity_id_t creature);

#endif // DAMAGE_SYSTEM_H
