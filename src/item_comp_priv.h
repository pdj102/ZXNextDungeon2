/**
 * @file item_comp_priv.h
 * @brief Private/internal declarations for item_comp.c
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `item_comp.c` and systems that operae on items). It should NOT be included by general modules.
 */

#ifndef ITEM_COMP_PRIV_H
#define ITEM_COMP_PRIV_H

#include <stdint.h>
#include "item_comp.h" /* pull in public item_comp_type_t and ITEM_KIND_COUNT */

#include "zxnext.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Item type base attributes - read only  */
typedef struct {
    const char *name;   
    zxnext_tile_t tile; 
    uint8_t weight;
    uint8_t value;
    uint8_t flags;
} item_comp_base_t;

/* Item component data per entity */
typedef struct {
    item_type_t type;   // index into item_comp_bases[]
    uint8_t quantity;       // stack size
} item_comp_t;



#endif /* ITEM_COMP_PRIV_H */

