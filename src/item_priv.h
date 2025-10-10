/**
 * @file item_priv.h
 * @brief Private/internal declarations for item.c
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `item.c`). It should NOT be included by general modules.
 */

#ifndef ITEM_PRIV_H
#define ITEM_PRIV_H

#include <stdint.h>
#include "item.h" /* pull in public item_type_t and ITEM_KIND_COUNT */

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Item type base attributes - read only  */
typedef struct {
    const char *name;   
    uint8_t sprite_id;
    uint8_t weight;
    uint8_t value;
    uint8_t flags;
} item_base_t;

/* Item component data per entity */
typedef struct {
    item_type_t type;   // index into item_bases[]
    uint8_t quantity;   // stack size
} item_component_t;



#endif /* ITEM_PRIV_H */

