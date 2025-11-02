/**
 * @file map_terrain_priv.h
 * @author Paul Johnson
 * @brief Private/internal declarations for map_terrain.c
 * 
 * @copyright Copyright (c) 2025
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `map_terrain.c`). It should NOT be included by general modules.*  
 */

#ifndef MAP_TERRAIN_PRIV_H
#define MAP_TERRAIN_PRIV_H

#include "map_terrain.h"

#include "map.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/



/* Map_terrain structure */
 typedef struct {
    terrain_type_t terrain[MAP_WIDTH][MAP_HEIGHT]; /* terrain data for the map_terrain */
} map_terrain_t;

/***************************************************
 * private function prototypes
 ***************************************************/

#endif // MAP_TERRAIN_PRIV_H
