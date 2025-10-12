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

/**
 * @brief Initialize creature component for an existing entity
 * 
 * @param id 
 */
uint8_t creature_init_for_entity(entity_id_t id, entity_kind_t kind, uint8_t quantity)
{
    util_assert(id < MAX_ENTITIES);
    util_assert(kind < CREATURE_KIND_COUNT);
    util_assert(quantity > 0);

    g.creature_components[id].kind = kind; /* set creature type */
    // todo

    entity_set_component(id, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
}

zxnext_tile_t *creature_get_tile(entity_id_t id)
{
    return &(creature_bases[g.creature_components[id].kind].tile);
}

/**
 * @brief Destroy creature component for an entity
 * 
 * @param id 
 */
void creature_destroy(entity_id_t id)
{
    entity_clear_component(id, COMPONENT_CREATURE); /* clear entity creature component mask */
}