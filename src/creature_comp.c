/**
 * @file creature_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "creature_comp.h"

#include "creature_comp_priv.h"

#include "global_state.h"
#include "entity.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/
const creature_comp_base_t creature_bases[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE]   = { "None",   {' ', 0}, CREATURE_CLASS_NONE, 0, 0, 0 },
    [CREATURE_RAT]    = { "Rat",   {'R', 0}, CREATURE_CLASS_BEASTS, 12, 7, 10},
    [CREATURE_HUMAN]  = { "Human", {'H', 0}, CREATURE_CLASS_HUMANOIDS, 10, 4, 10}
};


/***************************************************
 * public functions
 ***************************************************/
void creature_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.creature_components[i].kind = CREATURE_NONE; /* mark all creatures as none */
    }
}

uint8_t creature_add(entity_id_t entity, entity_kind_t kind)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(kind < CREATURE_KIND_COUNT);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    g.creature_components[entity].kind = kind; /* set creature type */
    // todo set up creature 

    entity_set_component(entity, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
}

zxnext_tile_t *creature_get_tile(entity_id_t id)
{
    return &(creature_bases[g.creature_components[id].kind].tile);
}

void creature_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_CREATURE))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_CREATURE); /* clear entity creature component mask */
}