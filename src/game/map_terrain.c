/**
 * @file map_terrain.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "map_terrain.h"

#include "map_terrain_priv.h"
#include "global_state.h"

/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void map_terrain_init(void)
{
    for (uint8_t x = 0; x < MAP_TERRAIN_WIDTH; x++) {
        for (uint8_t y = 0; y < MAP_TERRAIN_HEIGHT; y++) {
            g.map.terrain.terrain[x][y] = TERRAIN_FLOOR; /* default to floor */
        }
    }

    /* Create walls around the edges */
    for (uint8_t x = 0; x < MAP_TERRAIN_WIDTH; x++) {
        g.map.terrain.terrain[x][0] = TERRAIN_WALL;
        g.map.terrain.terrain[x][MAP_TERRAIN_HEIGHT - 1] = TERRAIN_WALL;
    }
    for (uint8_t y = 0; y < MAP_TERRAIN_HEIGHT; y++) {
        g.map.terrain.terrain[0][y] = TERRAIN_WALL;
        g.map.terrain.terrain[MAP_TERRAIN_WIDTH - 1][y] = TERRAIN_WALL;
    }
}

terrain_type_t map_terrain_get_terrain( uint8_t x, uint8_t y)
{
    if (x >= MAP_TERRAIN_WIDTH || y >= MAP_TERRAIN_HEIGHT) {
        return TERRAIN_NONE; /* out of bounds */
    }
    return g.map.terrain.terrain[x][y];
}

void map_terrain_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain)
{
    if (x >= MAP_TERRAIN_WIDTH || y >= MAP_TERRAIN_HEIGHT) {
        return; /* out of bounds */
    }
    if (terrain >= TERRAIN_TYPE_COUNT) {
        return; /* invalid terrain */
    }
    g.map.terrain.terrain[x][y] = terrain;
}