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
#include "components/item_comp.h"
#include "components/creature_comp.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

/*
 * @brief Create an item of a given kind
*/
entity_id_t entity_factory_create_item(item_kind_t type, uint8_t quantity);

/*
* @brief Create a monster of a given kind
*/
entity_id_t entity_factory_create_monster(creature_kind_t kind);

/*
* @brief Create player
*/
entity_id_t entity_factory_create_player( void );

#endif // ENTITY_FACTORY_H
