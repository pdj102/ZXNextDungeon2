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
