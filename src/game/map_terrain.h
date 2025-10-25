/**
 * @file map_terrain.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_TERRAIN_H
#define MAP_TERRAIN_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAP_TERRAIN_WIDTH 32
#define MAP_TERRAIN_HEIGHT 24

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    TERRAIN_NONE = 0,
    TERRAIN_WALL,
    TERRAIN_FLOOR,
    TERRAIN_TYPE_COUNT
} terrain_type_t;

/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void map_terrain_init(void);
terrain_type_t map_terrain_get_terrain( uint8_t x, uint8_t y);
void map_terrain_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain);

#endif // MAP_TERRAIN_H
