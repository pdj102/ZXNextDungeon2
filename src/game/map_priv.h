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

#include "map.h"

#include "../ecs/entity.h"

#include "map_terrain_priv.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/
typedef struct {
    map_terrain_t terrain;
    entity_id_t cell_head[MAP_WIDTH][MAP_HEIGHT];
} map_t;

/***************************************************
 * private variables
 ***************************************************/


/***************************************************
 * private function prototypes
 ***************************************************/

#endif // MAP_PRIV_H
