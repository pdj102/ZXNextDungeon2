/**
 * @file map.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "entity.h"

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAP_WIDTH 32
#define MAP_HEIGHT 24

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void map_init(void);
bool_t map_can_enter(entity_id_t entity, uint8_t x, uint8_t y);

#endif // MAP_TERRAIN_H
