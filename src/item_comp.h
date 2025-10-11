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
} item_comp_type_t;



/***************************************************
 * public function prototypes
 ***************************************************/
void item_init(void);
entity_id_t item_create(item_comp_type_t type, uint8_t quantity);
bool_t item_init_for_entity(entity_id_t entity, item_comp_type_t type, uint8_t quantity);
void item_destroy(entity_id_t id);

#endif // ITEM_COMP_H
