/**
 * @file name_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/name_comp.h"
#include "ecs/entity.h"

#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void name_add(entity_id_t entity, name_id_t name)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_NAME));

    g.name_components[entity] = name; 

    entity_set_component(entity, COMPONENT_NAME);
}

void name_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_NAME);
}



 /***************************************************
 * private functions
 ***************************************************/