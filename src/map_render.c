/**
 * @file map_render.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "map_render.h"

#include "zxnext.h"

#include "global_state.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/

 void map_render(void)
{
    for (uint8_t x = 0; x < TERRAIN_MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < TERRAIN_MAP_HEIGHT; y++) {
            
            if (g.location_cell_head[x][y] != ENTITY_ID_INVALID) {
                /* there is at least one entity at this location - render the top one */

            }
            terrain_type_t terrain = g.terrain_map.terrain[x][y];
            zxnext_tile_t tile = {0};
            switch (terrain) {
                case TERRAIN_WALL:
                    tile.tile_id = 1; /* wall tile */
                    tile.tile_attr = 0;
                    break;
                case TERRAIN_FLOOR:
                    tile.tile_id = 2; /* floor tile */
                    tile.tile_attr = 0;
                    break;
                default:
                    tile.tile_id = 0; /* empty tile */
                    tile.tile_attr = 0;
                    break;
            }
            zxnext_tilemap_set(x, y, &tile);
        }
    }
}