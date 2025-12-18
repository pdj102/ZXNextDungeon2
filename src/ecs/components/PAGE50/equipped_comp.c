/**
 * @file equipped_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/equipped_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void equipped_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.equipped_components[i].equipped_by = ENTITY_ID_INVALID;  
    }
}

uint8_t equipped_add(entity_id_t entity, entity_id_t equipped_by)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_components(entity, COMPONENT_EQUIPPED)); /* entity must not have equipped component */

    g.equipped_components[entity].equipped_by = equipped_by; 

    entity_set_component(entity, COMPONENT_EQUIPPED); /* set entity equipped component mask */

    return 1; /* success */
}

void equipped_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.equipped_components[entity].equipped_by == ENTITY_ID_INVALID);
    entity_clear_component(entity, COMPONENT_EQUIPPED); /* clear entity equipped component mask */
}

 /***************************************************
 * private functions
 ***************************************************/