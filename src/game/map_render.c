/**
 * @file map_render.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "map_render.h"

#include <stdlib.h>

#include "game/camera.h"
#include "game/map_terrain.h"

#include "game/global_state.h"

#include "core/zxnext.h"

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/

void map_render(void)
{
    zxnext_tile_t tile = {0};
    uint8_t map_x = g.camera.x;
    uint8_t map_y = g.camera.y;

    for (uint8_t x = 0; x < VIEW_WIDTH; x++)
    {
        for (uint8_t y = 0; y < VIEW_HEIGHT; y++)
        {
            if (g.map.cell_head[map_x][map_y] != ENTITY_ID_INVALID)
            {
                /* there is at least one entity at this location - render the top one */
                /* TODO implement a while loop to determine the highest priority entity to draw*/
                zxnext_tilemap_set(x, y, &g.renderable_components[g.map.cell_head[map_x][map_y]].tile);
            }
            else
            {
                terrain_type_t terrain = g.map.terrain[map_x][map_y];

                zxnext_tilemap_set(x, y, &terrain_bases[terrain].tile);
            }
            map_y++;
        }
        map_y = g.camera.y;
        map_x++;
    }
}

