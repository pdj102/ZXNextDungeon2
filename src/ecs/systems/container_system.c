/**
 * @file container_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "container_system.h"

#include <sys\types.h>

#include "../entity.h"
#include "../components/contained_comp.h"

#include "../../core/util.h"
#include "../../game/global_state.h"



/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void container_system_init(void)
{

}

bool_t container_place_item_in_container(entity_id_t container, entity_id_t item)
{
    util_assert(item < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(entity_has_component(container, COMPONENT_CONTAINER)); /* must not already be contained */
    util_assert(!entity_has_component(item, COMPONENT_LOCATION)); /* must not be placed on the map */

    if (g.container_components[container].count == g.container_components[container].capacity)
    {
        /* container is full */
        return 0;
    }

    contained_add(item);

    g.contained_components[item].next = g.container_components[container].head; /* set next to current container head */
    g.container_components[container].head = item; /* set container head to entity */
    g.contained_components[item].container = container;   /* contained item has a reference to container */
    g.container_components[container].count++;

    return 1;
}


void container_remove_item_from_container(entity_id_t container, entity_id_t item)
{
    util_assert(item < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));
    util_assert(entity_has_component(item, COMPONENT_CONTAINED));
 
    entity_id_t current = g.container_components[container].head; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == item) { /* found the item to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.container_components[container].head = g.contained_components[current].next; /* remove from head */
            } else {
                g.contained_components[prev].next = g.contained_components[current].next; /* bypass current */
            }
            g.contained_components[item].container = ENTITY_ID_INVALID; /* must clear .container to remove contained */
            contained_remove(item); /* remove contained component*/
            g.container_components[container].count--;
            return;
        }
        prev = current; 
        current = g.contained_components[current].next; /* move to next */
    }
    util_abort("Entity not found in container");
}

entity_id_t container_get_first(entity_id_t container)
{
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));

    return g.container_components[container].head;
}

uint8_t container_count(entity_id_t container)
{
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));

    return g.container_components[container].count;
}

entity_id_t container_get_next(entity_id_t entity)
{
    util_assert(entity_has_component(entity, COMPONENT_CONTAINED));

    return g.contained_components[entity].next;
}

/*
 * @brief If entity flagged for destruction, remove from any containing entity and mark all contained entities for destruction
 */
void container_system_clean_up(void)
{
for (entity_id_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (entity_has_flag(i, FLAG_PENDING_DESTORY))
        {
            if (entity_has_component(i, COMPONENT_CONTAINED))
            {
                container_remove_item_from_container(g.contained_components[i].container, i);
            }
            if (entity_has_component(i, COMPONENT_CONTAINER))
            {
                container_mark_contents_for_destruction(i);
            }
            entity_mark_for_destruction(i);
        }
    }    
}

/*
 * @brief Remove every item from the container and flag pending destruction
*/
void container_mark_contents_for_destruction(entity_id_t container)
{
    entity_id_t entity;

    entity = g.container_components[container].head;

    /* Keep removing items until head is empty */
    while (entity != ENTITY_ID_INVALID)
    {
        container_remove_item_from_container(container, entity);
        entity_mark_for_destruction(entity);

        entity = g.container_components[container].head;
    }

}