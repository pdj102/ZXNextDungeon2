/**
 * @file item.h
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
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
    ITEM_KIND_COUNT
} item_type_t;

typedef struct {
    item_type_t type;   // index into item_bases[]
    uint8_t quantity;   // stack size
} item_component_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);
entity_id_t entity_create(void);
void entity_destroy(entity_id_t id);

#endif // ITEM_H
