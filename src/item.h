/**
 * @file item.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_H
#define ITEM_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    ITEM_NONE = 0,
    ITEM_SWORD,
    ITEM_SHIELD,
    ITEM_POTION,
    ITEM_KEY,
    ITEM_TYPE_COUNT
} item_type_t;



/***************************************************
 * public function prototypes
 ***************************************************/
entity_id_t item_create(item_type_t type, uint8_t quantity);
void item_destroy(entity_id_t id);

#endif // ITEM_H
