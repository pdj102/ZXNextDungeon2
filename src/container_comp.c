/**
 * @file container_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "container_comp.h"

#include "container_comp_priv.h"
#include "global_state.h"

#include "entity.h"
#include "util.h"


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

/**
 * @brief Initialize container component for an existing entity
 * 
 * @param id 
 */
bool_t container_init_for_entity(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);

    entity_set_component(id, COMPONENT_CONTAINER); /* set entity container component mask */

    return 1; /* success */
}

void container_add(entity_id_t container, entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);    
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));
    util_assert(g.location_components[entity].type == LOC_NONE); /* entity must not be placed */

    g.location_components[entity].type = LOC_CONTAINER;
    g.location_components[entity].data.container = container;

    g.location_components[entity].next_in_location = g.container_components[container].head; /* set next to current head of this container */
    g.container_components[container].head = entity; /* set new head of this container */
}

void container_remove(entity_id_t container, entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));
    util_assert(g.location_components[entity].type == LOC_CONTAINER);

    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(g.location_components[entity].type == LOC_CONTAINER);

    entity_id_t current = g.container_components[container].head; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.container_components[container].head = g.location_components[current].next_in_location; /* remove from head */
            } else {
                g.location_components[prev].next_in_location = g.location_components[current].next_in_location; /* bypass current */
            }
            g.location_components[current].type = LOC_NONE; /* mark as not placed */
            g.location_components[current].next_in_location = ENTITY_ID_INVALID; /* clear next */
            return;
        }
        prev = current; 
        current = g.location_components[current].next_in_location; /* move to next */
    }
    util_abort("Entity not found in container");
}

/**
 * @brief Destroy container component for an entity
 * 
 * @param id 
 */
void container_destroy(entity_id_t id)
{
    entity_clear_component(id, COMPONENT_CONTAINER); /* clear entity container component mask */
}