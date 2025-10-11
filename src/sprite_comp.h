/**
 * @file sprite_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SPRITE_COMP_H
#define SPRITE_COMP_H

#include <stdint.h>

#include "entity.h"
#include "zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void sprite_init(void);
bool_t sprite_init_for_entity(entity_id_t entity, const zxnext_tile_t *tile_p);
void sprite_destroy(entity_id_t id);

#endif // SPRITE_COMP_H
