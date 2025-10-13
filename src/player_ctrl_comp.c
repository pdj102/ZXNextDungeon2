/**
 * @file player_ctrl_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "player_ctrl_comp.h"

#include <sys\types.h>

#include "global_state.h"
#include "entity.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void player_ctrl_init(void)
{
    g.player.id = ENTITY_ID_INVALID;
}

/**
 * @brief Initialize player_ctrl component for an existing entity
 * 
 * @param id 
 */
bool_t player_ctrl_init_for_entity(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    g.player.id = id;

    entity_set_component(id, COMPONENT_PLAYER_CTRL); /* set entity player_ctrl component mask */

    return 1; /* success */
}

/**
 * @brief Destroy player_ctrl component for an entity
 * 
 * @param id 
 */
void player_ctrl_destroy(entity_id_t id)
{
    g.player.id == ENTITY_ID_INVALID;

    entity_clear_component(id, COMPONENT_PLAYER_CTRL); /* clear entity player_ctrl component mask */
}