/**
 * @file contained_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/contained_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void contained_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        g.contained_components[i].container = ENTITY_ID_INVALID; /* mark all no container */
        g.contained_components[i].next = ENTITY_ID_INVALID; /* mark no next entity */
    }
}

/*
 * @brief Add a contained component to the entity and place the entity in the container entity e.g. add potion (item) to chest (container)
 */
void contained_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_components(entity, COMPONENT_CONTAINED)); /* entity must not have contained component */
    util_assert(!entity_has_components(entity, COMPONENT_LOCATION)); /* entity must not have location component */

    entity_set_component(entity, COMPONENT_CONTAINED); /* set entity contained component mask */    
}

/*
 * @brief Remove the contained entity from its container and remove its contained component e.g. remove potion (item) from a chest (container)
*/
void contained_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.contained_components[entity].container == ENTITY_ID_INVALID); /* entity must not be in a container */

    entity_clear_component(entity, COMPONENT_CONTAINED);
}