/**
 * @file map_priv.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_PRIV_H
#define MAP_PRIV_H

#include "game/map.h"
#include "game/map_terrain.h"
#include "map_render.h"

#include "ecs/entity.h"



/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/
typedef struct {
    uint8_t terrain[MAP_WIDTH][MAP_HEIGHT]; /* terrain data - uint8_t (not enum) ensures 1 byte per cell to fit in 8KB slot 7 */
    entity_id_t entity_head[MAP_WIDTH][MAP_HEIGHT];
} map_t;

__at (0xe000) static map_t map; /* Map data in fixed 8k MMU slot 7 */

/***************************************************
 * private variables
 ***************************************************/


/***************************************************
 * private function prototypes
 ***************************************************/

#endif // MAP_PRIV_H
