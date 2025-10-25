/**
 * @file map_render.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "map_render.h"

#include "global_state.h"

#include "../core/zxnext.h"

/***************************************************
 * private types
 * ***************************************************/
/* Terrain type base attributes - read only  */
typedef struct {
    const char *name;   
    zxnext_tile_t tile;
} terrain_base_t;

/***************************************************
 * private variables
 * ***************************************************/
const terrain_base_t terrain_bases[TERRAIN_TYPE_COUNT] = {
    [TERRAIN_NONE]   = { "None",   {'X', 0} },
    [TERRAIN_WALL]   = { "Wall",   {'#', 0} },
    [TERRAIN_FLOOR]  = { "Floor",  {'.', 0} }
};

/***************************************************
 * public functions
 ***************************************************/

void map_render(void)
{
    zxnext_tile_t tile = {0};

    for (uint8_t x = 0; x < MAP_TERRAIN_WIDTH; x++)
    {
        for (uint8_t y = 0; y < MAP_TERRAIN_HEIGHT; y++)
        {

            if (g.map.cell_head[x][y] != ENTITY_ID_INVALID)
            {
                /* there is at least one entity at this location - render the top one */
                zxnext_tilemap_set(x, y, &g.sprite_components[g.map.cell_head[x][y]].tile);
            }
            else
            {
                terrain_type_t terrain = g.map.terrain.terrain[x][y];

                zxnext_tilemap_set(x, y, &terrain_bases[terrain].tile);
            }
        }
    }
}