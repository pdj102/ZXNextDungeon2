/**
 * @file player_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "player_comp.h"

#include <sys\types.h>      /* bool_t */

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void player_init(void)
{
    g.player.id == ENTITY_ID_INVALID;
}

/*
 * There can only be one player ctrl component 
*/
void player_add(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    g.player.id = id;

    entity_set_component(id, COMPONENT_PLAYER); /* set entity player_ctrl component mask */
}

void player_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_PLAYER))
    {
        return;
    }

    g.player.id == ENTITY_ID_INVALID;

    entity_clear_component(entity, COMPONENT_PLAYER); /* clear entity player_ctrl component mask */
}