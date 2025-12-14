/**
 * @file equippable_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/equippable_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void equippable_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.equippable_components[i].slot = EQUIPPABLE_NONE;
    }
}

uint8_t equippable_add(entity_id_t entity, equippable_slot_t slot)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EQUIPPABLE)); /* entity must not have equippable component */

    g.equippable_components[entity].slot = slot; 

    entity_set_component(entity, COMPONENT_EQUIPPABLE); /* set entity equippable component mask */

    return 1; /* success */
}

void equippable_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_EQUIPPABLE); /* clear entity equippable component mask */
}

 /***************************************************
 * private functions
 ***************************************************/