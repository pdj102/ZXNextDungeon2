/**
 * @file sprite_comp_priv.h
 * @brief Private/internal declarations for sprite_comp.c
 *
 * This header exposes internal sprite definitions only to files that need them
 * (primarily `sprite_comp.c` and systems that operate on sprites). It should NOT be included by general modules.
 */

#ifndef SPRITE_COMP_PRIV_H
#define SPRITE_COMP_PRIV_H

#include <stdint.h>
#include "sprite_comp.h" /* pull in public sprite_comp_type_t and SPRITE_KIND_COUNT */

#include "zxnext.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Sprite component data per entity */
typedef struct {
    zxnext_tile_t tile;   // tile to use for this sprite
} sprite_comp_t;

typedef sprite_comp_t sprite_components_t[MAX_ENTITIES]; /* sprite component data */

/***************************************************
 * private function prototypes
 ***************************************************/

#endif /* SPRITE_COMP_PRIV_H */

