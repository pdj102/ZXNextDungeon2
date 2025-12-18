/**
 * @file renderable_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "renderable_comp.h"

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
void renderable_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.renderable_components[i].tile.tile_id = 'X'; 
        g.renderable_components[i].tile.tile_attr = 0;
    }
}

void renderable_add(entity_id_t id, const zxnext_tile_t tile )
{
    util_assert(id < MAX_ENTITIES);

    g.renderable_components[id].tile = tile;

    entity_set_component(id, COMPONENT_RENDERABLE); /* set entity renderable component mask */
}

void renderable_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_RENDERABLE))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_RENDERABLE); /* clear entity renderable component mask */
}