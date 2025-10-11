/**
 * @file item_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_COMP_H
#define ITEM_COMP_H

#include <stdint.h>

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
void item_init(void);

uint8_t item_init_for_entity(entity_id_t id, entity_type_t type, uint8_t quantity);

zxnext_tile_t *item_get_tile(entity_id_t id);

void item_destroy(entity_id_t id);

#endif // ITEM_COMP_H
