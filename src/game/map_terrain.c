/**
 * @file map_terrain.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/map_terrain.h"

#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void map_terrain_init(void)
{
    /*
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
            g.map.terrain[x][y] = TERRAIN_FLOOR; 
        }
    }

    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        g.map.terrain[x][0] = TERRAIN_WALL;
        g.map.terrain[x][MAP_HEIGHT - 1] = TERRAIN_WALL;
    }
    for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
        g.map.terrain[0][y] = TERRAIN_WALL;
        g.map.terrain[MAP_WIDTH - 1][y] = TERRAIN_WALL;
    }
    */
}

terrain_type_t map_terrain_get_terrain( uint8_t x, uint8_t y)
{
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT) {
        return TERRAIN_NONE; /* out of bounds */
    }
    return g.map.terrain[x][y];
}

void map_terrain_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain)
{
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT) {
        return; /* out of bounds */
    }
    if (terrain >= TERRAIN_TYPE_COUNT) {
        return; /* invalid terrain */
    }
    g.map.terrain[x][y] = terrain;
}