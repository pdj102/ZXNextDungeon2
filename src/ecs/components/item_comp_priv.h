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

#include "ecs/components/item_comp.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Item component data per entity */
typedef struct {
    item_kind_t kind;       // index into item_comp_bases[]
    uint8_t quantity;       // stack size
} item_comp_t;

typedef item_comp_t item_components_t[MAX_ENTITIES]; /* item component data */

 /***************************************************
 * private functions prototypes
 ***************************************************/

#endif /* ITEM_COMP_PRIV_H */

