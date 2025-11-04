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
            /* remove container component*/
            contained_remove(item);
            return;
        }
        prev = current; 
        current = g.contained_components[current].next; /* move to next */
    }
    util_abort("Entity not found in container");
}

void container_remove_entity(entity_id_t entity)
{
    entity_id_t container = g.contained_components[entity].container;
    contained_remove(entity);
    g.container_components[container].count--;

    /* TODO move the removal code here and make contained_remove just remove the component checking not longer contained*/
}

void container_destroy_contents(entity_id_t container)
{
    entity_id_t entity;

    entity = g.container_components[container].head;

    while (entity != ENTITY_ID_INVALID)
    {
        container_remove_entity(entity);
        entity_set_flag(entity, FLAG_PENDING_DESTORY);
    }

}