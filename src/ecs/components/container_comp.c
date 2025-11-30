/**
 * @file container_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "container_comp.h"

#include "ecs/components/container_comp_priv.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


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

    util_assert(g.container_components[entity].head == ENTITY_ID_INVALID); /* check container has no contained entities */

    entity_clear_component(entity, COMPONENT_CONTAINER); /* clear entity container component mask */
}