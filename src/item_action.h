/**
 * @file item_action.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_ACTION_H
#define ITEM_ACTION_H

#include <stdint.h>
#include <sys/types.h>

#include "entity.h"

#include "zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

bool_t item_action_try_pickup(entity_id_t entity, entity_id_t item);

#endif // ITEM_ACTION_H
