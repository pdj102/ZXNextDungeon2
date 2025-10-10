/**
 * @file map.h
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_H
#define MAP_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAP_WIDTH 32
#define MAP_HEIGHT 24

/***************************************************
 * public types
 ***************************************************/
typedef struct {
    uint8_t tiles[MAP_WIDTH][MAP_HEIGHT]; /* tile data for the map */
} map_t;
/***************************************************
 * public function prototypes
 ***************************************************/
void map_init(map_t *map_p);
uint8_t map_get_tile(const map_t *map_p, uint8_t x, uint8_t y);
void map_set_tile(map_t *map_p, uint8_t x, uint8_t y, uint8_t tile);
#endif // MAP_H
