/**
 * @file ai_system.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

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
void ai_system_init(void);
void ai_system_process_entity_turn(entity_id_t entity);

#endif // AI_SYSTEM_H
