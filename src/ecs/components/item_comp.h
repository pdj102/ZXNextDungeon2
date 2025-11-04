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

#include "../entity.h"

#include "../../core/text.h"
#include "../../core/zxnext.h"

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
} item_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void item_init(void);

uint8_t item_add(entity_id_t entity, item_kind_t type, uint8_t quantity);

void item_get_tile(entity_id_t id, zxnext_tile_t *tile);

void item_print_name(text_window_t *win, entity_id_t item);

void item_remove(entity_id_t entity);

#endif // ITEM_COMP_H
