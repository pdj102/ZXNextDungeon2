/**
 * @file movement_system.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <stdint.h>

#include "../entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void movement_system_init(void);
void movement_system_try_move(entity_id_t entity, int8_t dx, int8_t dy);

#endif // MOVEMENT_SYSTEM_H
