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
#include <sys/types.h>

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
uint8_t perception_system_try_check(entity_id_t creature);


#endif // PERCEPTION_SYSTEM_H
