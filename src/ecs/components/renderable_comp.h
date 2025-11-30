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

#include "../entity.h"
#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void renderable_init(void);
bool_t renderable_add(entity_id_t entity, const zxnext_tile_t *tile_p);
void renderable_remove(entity_id_t entity);

#endif // renderable_COMP_H
