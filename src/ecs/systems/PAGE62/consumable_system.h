/**
 * @file consumable_system.h
 * @author Paul Johnson
 * @brief consumable system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONSUMABLE_SYSTEM_H
#define CONSUMABLE_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
bool consumable_system_try_consume(entity_id_t actor, entity_id_t entity);

#endif // CONSUMABLE_SYSTEM_H
