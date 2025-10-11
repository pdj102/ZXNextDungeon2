/**
 * @file terrain_map_priv.h
 * @author Paul Johnson
 * @brief Private/internal declarations for terrain_map.c
 * 
 * @copyright Copyright (c) 2025
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `terrain_map.c`). It should NOT be included by general modules.*  
 */

#ifndef TERRAIN_MAP_PRIV_H
#define TERRAIN_MAP_PRIV_H

#include "terrain_map.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Terrain type base attributes - read only  */
typedef struct {
    const char *name;   
    char symbol;
} terrain_base_t;

/* Terrain_map structure */
 typedef struct {
    terrain_type_t terrain[TERRAIN_MAP_WIDTH][TERRAIN_MAP_HEIGHT]; /* terrain data for the terrain_map */
} terrain_map_t;

/***************************************************
 * private function prototypes
 ***************************************************/

#endif // TERRAIN_MAP_PRIV_H
