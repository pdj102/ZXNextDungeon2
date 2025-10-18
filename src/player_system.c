/**
 * @file player_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "player_system.h"

#include <sys\types.h>

#include "global_state.h"
#include "entity.h"
#include "location_comp.h"
#include "map.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/

 void try_move(void)
 {
    uint8_t x;
    uint8_t y;

    x = g.location_components[g.player.id].x;
    y = g.location_components[g.player.id].y;

    x++;

    if (map_can_enter(g.player.id, x, y))
    {
        location_move(g.player.id, x, y);
    }
 }

/***************************************************
 * public functions
 ***************************************************/
void player_system_init(void)
{
}

void player_system_update(void)
{
    uint8_t entity = g.player.id;

    if ( (entity == ENTITY_ID_INVALID) || (!entity_has_component(entity, COMPONENT_PLAYER_CTRL) ))
    {
        return; /* no player */
    }

    /* TODO checking if creature component is alive */

    try_move();
}
