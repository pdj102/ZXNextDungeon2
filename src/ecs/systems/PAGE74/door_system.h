/**
 * @file door_system.h
 * @author Paul Johnson
 * @brief Doors system
 */

#ifndef DOOR_SYSTEM_H
#define DOOR_SYSTEM_H

#include "ecs/entity.h"
#include "core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/

bool door_system_try_open(entity_id_t actor, entity_id_t entity);
bool door_system_try_close(entity_id_t actor, entity_id_t entity);

#endif // DOOR_SYSTEM_H
