/**
 * @file item_system.h
 * @author Paul Johnson
 * @brief Items are physical objects in game world.
 */

#ifndef ITEM_SYSTEM_H
#define ITEM_SYSTEM_H

#include "ecs/components/PAGE50/item_comp.h"

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

void item_system_init(void);

entity_id_t item_system_create(item_kind_t kind, uint8_t quantity);

void item_system_print_name(text_window_t *win, item_kind_t kind);

#endif // ITEM_BASE_H
