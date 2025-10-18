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
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/

 movement

/***************************************************
 * public functions
 ***************************************************/
void player_system_init(void)
{
}

void player_system_update(void)
{
    uint8_t entity = g.player.id;

    if ( (entity == ENTITY_ID_INVALID) || (!entity_has_component(entity, COMPONENT_PLAYER_SYSTEM) ))
    {
        return; /* no player */
    }

    /* TODO checking if creature component is alive */

    movement_try(entity, 1, 0);
}
