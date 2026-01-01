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
#include "ecs/components/destructible_comp.h"

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
int8_t healing_system_try(entity_id_t actor, int8_t amount, healing_kind_t kind);

#endif // HEALING_SYSTEM_H
