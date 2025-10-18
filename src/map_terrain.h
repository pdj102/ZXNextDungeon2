/**
 * @file terrain_map.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define TERRAIN_MAP_WIDTH 32
#define TERRAIN_MAP_HEIGHT 24

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
void terrain_map_init(void);
terrain_type_t terrain_map_get_terrain( uint8_t x, uint8_t y);
void terrain_map_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain);

#endif // TERRAIN_MAP_H
