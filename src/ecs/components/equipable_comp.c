/**
 * @file equipable_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/equipable_comp.h"

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
void equipable_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.equipable_components[i].slot = EQUIPABLE_NONE;                 
        g.equipable_components[i].equipped_by = ENTITY_ID_INVALID;  
    }
}

uint8_t equipable_add(entity_id_t entity, equipable_slot_t slot)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EQUIPABLE)); /* entity must not have equipable component */

    g.equipable_components[entity].slot = slot; 
    g.equipable_components[entity].equipped_by = ENTITY_ID_INVALID; 

    entity_set_component(entity, COMPONENT_EQUIPABLE); /* set entity equipable component mask */

    return 1; /* success */
}

void equipable_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.equipable_components[entity].equipped_by == ENTITY_ID_INVALID);
    entity_clear_component(entity, COMPONENT_EQUIPABLE); /* clear entity equipable component mask */
}

 /***************************************************
 * private functions
 ***************************************************/