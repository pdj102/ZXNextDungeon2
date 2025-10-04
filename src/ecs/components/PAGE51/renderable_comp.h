/**
 * @file renderable_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef renderable_COMP_H
#define renderable_COMP_H

#include <stdint.h>

#include "ecs/entity.h"
#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* renderable component data per entity */
typedef struct {
    zxnext_tile_t tile;   /* tile to use for this renderable */
} renderable_comp_t;

typedef renderable_comp_t renderable_components_t[MAX_ENTITIES]; /* renderable component data */

/***************************************************
 * public function prototypes
 ***************************************************/
void renderable_add(entity_id_t entity, const zxnext_tile_t tile);
void renderable_remove(entity_id_t entity);

#endif // renderable_COMP_H
