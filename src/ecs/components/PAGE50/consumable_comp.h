/**
 * @file consumable_comp.h
 * @author Paul Johnson
 * @brief ECS consumable component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONSUMABLE_COMP_H
#define CONSUMABLE_COMP_H

#include <stdint.h>

#include "core/util.h"

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
void consumable_init(void);

void consumable_add(entity_id_t entity);

void consumable_remove(entity_id_t entity);

#endif // CONSUMABLE_COMP_H
