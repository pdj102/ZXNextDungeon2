/**
 * @file transition_system.h
 * @author Paul Johnson
 * @brief Transitions system
 */

#ifndef TRANSITION_SYSTEM_H
#define TRANSITION_SYSTEM_H

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

bool transition_system_try(entity_id_t source, entity_id_t target);

#endif // TRANSITION_SYSTEM_H
