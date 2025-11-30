/**
 * @file player_ctrl_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "player_ctrl_comp.h"

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
void player_ctrl_init(void)
{
    g.player.id = ENTITY_ID_INVALID;
    g.player.head = ENTITY_ID_INVALID;
    g.player.neck = ENTITY_ID_INVALID;
    g.player.body = ENTITY_ID_INVALID;
    g.player.hands = ENTITY_ID_INVALID;
    g.player.left_finger = ENTITY_ID_INVALID;
    g.player.right_finger = ENTITY_ID_INVALID;
    g.player.melee_weapon = ENTITY_ID_INVALID;
    g.player.ranged_weapon = ENTITY_ID_INVALID;
    g.player.quiver = ENTITY_ID_INVALID;
    g.player.legs = ENTITY_ID_INVALID;
    g.player.feet = ENTITY_ID_INVALID;
}

/*
 * There can only be one player ctrl component 
*/
bool_t player_ctrl_add(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    g.player.id = id;

    entity_set_component(id, COMPONENT_PLAYER_CTRL); /* set entity player_ctrl component mask */

    return 1; /* success */
}

void player_ctrl_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_PLAYER_CTRL))
    {
        return;
    }

    g.player.id == ENTITY_ID_INVALID;

    entity_clear_component(entity, COMPONENT_PLAYER_CTRL); /* clear entity player_ctrl component mask */
}