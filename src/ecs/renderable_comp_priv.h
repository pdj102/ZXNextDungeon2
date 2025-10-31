/**
 * @file renderable_comp_priv.h
 * @brief Private/internal declarations for renderable_comp.c
 *
 * This header exposes internal renderable definitions only to files that need them
 * (primarily `renderable_comp.c` and systems that operate on renderables). It should NOT be included by general modules.
 */

#ifndef renderable_COMP_PRIV_H
#define renderable_COMP_PRIV_H

#include <stdint.h>
#include "renderable_comp.h" /* pull in public renderable_comp_type_t and renderable_KIND_COUNT */

#include "../core/zxnext.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* renderable component data per entity */
typedef struct {
    zxnext_tile_t tile;   // tile to use for this renderable
} renderable_comp_t;

typedef renderable_comp_t renderable_components_t[MAX_ENTITIES]; /* renderable component data */

/***************************************************
 * private function prototypes
 ***************************************************/

#endif /* renderable_COMP_PRIV_H */

