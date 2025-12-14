/**
 * @file creature_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/creature_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
void creature_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        // g.creature_components[i].kind = CREATURE_NONE; /* mark all creatures as none */
    }
}

uint8_t creature_add(entity_id_t entity, creature_kind_t kind, uint8_t challenge)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    g.creature_components[entity].kind = kind; /* set entity creature kind */
    g.creature_components[entity].challenge = challenge; /* set entity creature kind */

    entity_set_component(entity, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
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