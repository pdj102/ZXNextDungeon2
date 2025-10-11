/**
 * @file sprite_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sprite_comp.h"

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
void sprite_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.sprite_components[i].tile.tile_id = 'X'; 
        g.sprite_components[i].tile.tile_attr = 0;
    }
}

/**
 * @brief Initialize sprite component for an existing entity
 * 
 * @param id 
 */
bool_t sprite_init_for_entity(entity_id_t id, const zxnext_tile_t *tile_p )
{
    util_assert(id < MAX_ENTITIES);

    g.sprite_components[id].tile = *tile_p;

    entity_set_component(id, COMPONENT_SPRITE); /* set entity sprite component mask */

    return 1; /* success */
}

/**
 * @brief Destroy sprite component for an entity
 * 
 * @param id 
 */
void sprite_destroy(entity_id_t id)
{
    entity_clear_component(id, COMPONENT_SPRITE); /* clear entity sprite component mask */
}