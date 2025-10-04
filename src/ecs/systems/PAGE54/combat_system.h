/**
 * @file combat_system.h
 * @author Paul Johnson
 * @brief combat system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void combat_system_init(void);
bool_t combat_system_try_melee_attack(entity_id_t creature, entity_id_t target);

#endif // COMBAT_SYSTEM_H
