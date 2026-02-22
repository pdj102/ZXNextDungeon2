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
#include "ecs/components/destructible_comp.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
int8_t damage_system_try_take_damage(entity_id_t target, entity_id_t source, int8_t damage, damage_flag_t flag);
bool damage_system_try_kill(entity_id_t target, entity_id_t source);

#endif // DAMAGE_SYSTEM_H
