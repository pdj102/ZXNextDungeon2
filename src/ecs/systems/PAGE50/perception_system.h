/**
 * @file perception_system.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PERCEPTION_SYSTEM_H
#define PERCEPTION_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
bool perception_system_try_check(entity_id_t creature);
bool perception_system_can_see_target(entity_id_t ai, entity_id_t target);


#endif // PERCEPTION_SYSTEM_H
