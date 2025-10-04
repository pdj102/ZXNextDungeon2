/**
 * @file actions_system.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include <stdint.h>
#include <sys/types.h>

#include "ecs/entity.h"

#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void actions_system_init(void);

bool_t actions_system_try_quaff(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_eat(entity_id_t creature, entity_id_t item);

bool_t actions_system_try_open(entity_id_t creature, entity_id_t feature);
bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature);


#endif // ACTIONS_SYSTEM_H
