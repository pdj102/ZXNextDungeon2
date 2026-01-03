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
    terrain_type_t terrain[MAP_WIDTH][MAP_HEIGHT]; /* terrain data for the map_terrain */
    entity_id_t cell_head[MAP_WIDTH][MAP_HEIGHT];
} map_t;

/***************************************************
 * private variables
 ***************************************************/


/***************************************************
 * private function prototypes
 ***************************************************/

#endif // MAP_PRIV_H
