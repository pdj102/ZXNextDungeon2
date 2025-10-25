/**
 * @file map.c
 * @author Paul Johnson
 * @brief Game map 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "map.h"

#include <sys\types.h>      /* bool_t */

#include "../ecs/entity.h"
#include "../ecs/location_comp.h"

#include "map_terrain.h"
#include "global_state.h"
#include "../core/util.h"

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/

void map_init(void)
{

}

bool_t map_can_enter(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert( entity < MAX_ENTITIES );
    util_assert( x < MAP_WIDTH);
    util_assert( y < MAP_HEIGHT);

    if (g.map.terrain.terrain[x][y] == TERRAIN_FLOOR)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}