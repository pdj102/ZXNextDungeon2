/**
 * @file terrain_map.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "terrain_map.h"

#include "terrain_map_priv.h"

#include "global_state.h"


/***************************************************
 * private variables
 * ***************************************************/
const terrain_base_t terrain_bases[TERRAIN_TYPE_COUNT] = {
    [TERRAIN_NONE]   = { "None",   'X' },
    [TERRAIN_WALL]   = { "Wall",   '#' },
    [TERRAIN_FLOOR]  = { "Floor",  '.' }
};

/***************************************************
 * public functions
 ***************************************************/
void terrain_map_init(void)
{
    for (uint8_t x = 0; x < TERRAIN_MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < TERRAIN_MAP_HEIGHT; y++) {
            g.terrain_map.terrain[x][y] = TERRAIN_FLOOR; /* default to floor */
        }
    }

    /* Create walls around the edges */
    for (uint8_t x = 0; x < TERRAIN_MAP_WIDTH; x++) {
        g.terrain_map.terrain[x][0] = TERRAIN_WALL;
        g.terrain_map.terrain[x][TERRAIN_MAP_HEIGHT - 1] = TERRAIN_WALL;
    }
    for (uint8_t y = 0; y < TERRAIN_MAP_HEIGHT; y++) {
        g.terrain_map.terrain[0][y] = TERRAIN_WALL;
        g.terrain_map.terrain[TERRAIN_MAP_WIDTH - 1][y] = TERRAIN_WALL;
    }
}

terrain_type_t terrain_map_get_terrain( uint8_t x, uint8_t y)
{
    if (x >= TERRAIN_MAP_WIDTH || y >= TERRAIN_MAP_HEIGHT) {
        return TERRAIN_NONE; /* out of bounds */
    }
    return g.terrain_map.terrain[x][y];
}

void terrain_map_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain)
{
    if (x >= TERRAIN_MAP_WIDTH || y >= TERRAIN_MAP_HEIGHT) {
        return; /* out of bounds */
    }
    if (terrain >= TERRAIN_TYPE_COUNT) {
        return; /* invalid terrain */
    }
    g.terrain_map.terrain[x][y] = terrain;
}