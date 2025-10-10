/**
 * @file map_priv.h
 * @author Paul Johnson
 * @brief Private/internal declarations for map.c
 * 
 * @copyright Copyright (c) 2025
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `map.c`). It should NOT be included by general modules.*  
 */

#ifndef MAP_PRIV_H
#define MAP_PRIV_H

#include "map.h"

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

/* Map structure */
 typedef struct {
    terrain_type_t terrain[MAP_WIDTH][MAP_HEIGHT]; /* terrain data for the map */
} map_t;

/***************************************************
 * private function prototypes
 ***************************************************/

#endif // MAP_PRIV_H
