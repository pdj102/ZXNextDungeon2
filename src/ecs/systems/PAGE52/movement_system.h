/**
 * @file location_comp.h
 * @author Paul Johnson
 * @brief location component for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOCATION_COMP_H
#define LOCATION_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
bool_t movement_system_try_move(entity_id_t actor, int8_t dx, int8_t dy);
bool_t movement_system_location_equal(entity_id_t entity1, entity_id_t entity2);

#endif // LOCATION_COMP_H
