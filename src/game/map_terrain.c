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
 const terrain_base_t terrain_bases[TERRAIN_TYPE_COUNT] = {
    [TERRAIN_NONE]   = { "None",   {'X', 0}, TERRAIN_FLAGS_NONE },
    [TERRAIN_WALL]   = { "Wall",   {'#', 0}, TERRAIN_FLAG_BLOCKS_MOVE | TERRAIN_FLAG_BLOCKS_LOS },
    [TERRAIN_FLOOR]  = { "Floor",  {'.', 0}, TERRAIN_FLAGS_NONE  }
};

/***************************************************
 * public functions
 ***************************************************/
void map_terrain_init(void)
{

}

terrain_type_t map_terrain_get_terrain( uint8_t x, uint8_t y)
{
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT) {
        return TERRAIN_NONE; /* out of bounds */
    }
    return map.terrain[x][y];
}

void map_terrain_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain)
{
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT) {
        return; /* out of bounds */
    }
    if (terrain >= TERRAIN_TYPE_COUNT) {
        return; /* invalid terrain */
    }
    map.terrain[x][y] = terrain;
}