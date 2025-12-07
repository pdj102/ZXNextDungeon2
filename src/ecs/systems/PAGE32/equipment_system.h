/**
 * @file item_base.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_BASE_H
#define ITEM_BASE_H

#include "ecs/components/item_comp.h"

#include "core/text.h"


/***************************************************
 * public defines
 ***************************************************/
/* Item type base attributes - read only  */
typedef struct {
    item_class_t class;  // type of item (e.g. weapon, armor, consumable)
    const char *name;
    zxnext_tile_t tile; 
    uint8_t weight;
    uint8_t value;
    uint8_t flags;
} equipment_base_t;

/***************************************************
 * public types
 ***************************************************/
extern const equipment_base_t equipment_bases[];

/***************************************************
 * public function prototypes
 ***************************************************/

void equipment_system_init(void);

entity_id_t equipment_system_create(item_kind_t kind, uint8_t quantity);

void equipment_system_print_name(text_window_t *win, item_kind_t kind);

void equipment_system_get_tile(entity_id_t id, zxnext_tile_t *tile);

item_class_t equipment_system_get_class(item_kind_t kind);

#endif // ITEM_BASE_H
