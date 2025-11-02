/**
 * @file container_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "container_comp.h"

#include "container_comp_priv.h"
#include "contained_comp.h"
#include "entity.h"

#include "../game/global_state.h"
#include "../core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void container_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        g.container_components[i].head = ENTITY_ID_INVALID; /* mark all containers as empty */
    }
}


bool_t container_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINER)); /* entity must not have container component */

    g.container_components[entity].head = ENTITY_ID_INVALID; 
    g.container_components[entity].capacity = 10;
    g.container_components[entity].count = 0; 

    entity_set_component(entity, COMPONENT_CONTAINER); /* set entity container component mask */

    return 1; /* success */
}

void container_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_component(entity, COMPONENT_CONTAINER))
    {
        return;
    }

    util_assert(g.container_components[entity].head == ENTITY_ID_INVALID); /* check container has no contained entities */

    entity_clear_component(entity, COMPONENT_CONTAINER); /* clear entity container component mask */
}

bool_t container_add_entity(entity_id_t container, entity_id_t entity)
{
    if (g.container_components[container].count < g.container_components[container].capacity)
    { /* check if container is full */
        contained_add(entity, container); /* add entity to container */
        g.container_components[container].count++;
        return 1;
    }
    return 0;
}

void container_remove_entity(entity_id_t entity)
{
    entity_id_t container = g.contained_components[entity].container;
    contained_remove(entity);
    g.container_components[container].count--;
}