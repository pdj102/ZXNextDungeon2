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

    for (uint8_t vx = 0; vx < VIEW_WIDTH; vx++)
    {
        for (uint8_t vy = 0; vy < VIEW_HEIGHT; vy++)
        {
            if (map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
            {
                /* Out of bounds - skip this tile */
                map_y++;
                continue;
            }

            if (g.map.entity_head[map_x][map_y] != ENTITY_ID_INVALID)
            {
                /* there is at least one entity at this location - render the top one */
                /* TODO implement a while loop to determine the highest priority entity to draw*/
                zxnext_tilemap_set(vx, vy, &g.renderable_components[g.map.entity_head[map_x][map_y]].tile);
            }
            else
            {
                terrain_type_t terrain = g.map.terrain[map_x][map_y];

                zxnext_tilemap_set(vx, vy, &terrain_bases[terrain].tile);
            }
            map_y++;
        }
        map_y = g.camera.y;
        map_x++;
    }
}

