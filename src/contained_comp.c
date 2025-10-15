/**
 * @file contained_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "contained_comp.h"

#include "contained_comp_priv.h"
#include "global_state.h"

#include "entity.h"
#include "util.h"


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

/**
 * @brief Initialize contained component for an existing entity
 * 
 * @param id 
 */
bool_t contained_init_for_entity(entity_id_t id)
{
    /* TODO remove init */
    util_assert(id < MAX_ENTITIES);

    return 1; /* success */
}

void contained_add(entity_id_t container, entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);    
    util_assert(entity_has_component(container, COMPONENT_CONTAINER)); /* container entity must have container component*/
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINED)); /* entity must not have contained component */
    util_assert(!entity_has_component(entity, COMPONENT_LOCATION)); /* entity must not have location component */

    g.contained_components[entity].next = g.container_components[container].head; /* set next to current container head */
    g.container_components[entity].head = entity; /* set container head to entity */

    entity_set_component(entity, COMPONENT_CONTAINED); /* set entity contained component mask */    
}

void contained_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_CONTAINED));

    entity_id_t container = g.contained_components[entity].container;

    entity_id_t current = g.container_components[container].head; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.container_components[container].head = g.contained_components[current].next; /* remove from head */
            } else {
                g.contained_components[prev].next = g.contained_components[current].next; /* bypass current */
            }
            g.contained_components[current].next = ENTITY_ID_INVALID; /* clear next */
            entity_clear_component(entity, COMPONENT_CONTAINED);
            return;
        }
        prev = current; 
        current = g.contained_components[current].next; /* move to next */
    }
    util_abort("Entity not found in contained");
}

/**
 * @brief Destroy contained component for an entity
 * 
 * @param id 
 */
void contained_destroy(entity_id_t id)
{
    contained_remove(id);
}