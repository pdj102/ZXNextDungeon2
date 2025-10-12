/**
 * @file entity_factory.h
 * @author Paul Johnson
 * @brief Entity_factory for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <stdint.h>
#include <sys/types.h>

#include "entity.h"
#include "item_comp.h"
#include "creature_comp.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

entity_id_t entity_factory_create_item(item_kind_t type, uint8_t quantity);


#endif // ENTITY_FACTORY_H
