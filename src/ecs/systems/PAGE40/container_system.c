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

#include "ecs/entity.h"
#include "ecs/components/contained_comp.h"

#include "core/util.h"
#include "game/global_state.h"



/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void container_system_init(void)
{

}

bool_t container_system_place_item_in(entity_id_t container, entity_id_t item)
{
    util_assert(item < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(!entity_has_component(item, COMPONENT_CONTAINED)); /* must not already be contained */
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


void container_system_remove_item_from(entity_id_t container, entity_id_t item)
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

/*
 * @brief Returns the number of entities in the specified container. 
 * @param container The ID of the container
 * @return The number of entities in the container
 */
uint8_t container_system_count(entity_id_t container)
{
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));

    return g.container_components[container].count;
}

/*
 * @brief Returns the first entity in the specified container
 * @param container The ID of the container
 * @return The first entity in the container
 */
entity_id_t container_system_get_first(entity_id_t container)
{
    util_assert(entity_has_component(container, COMPONENT_CONTAINER));

    return g.container_components[container].head;
}

/*
 * @brief Returns the next entity after the specified entity in the same container
 * @param entity The ID of the entity to find the next one
 * @return The next entity after the specified entity or ENTITY_ID_INVALID
 */
entity_id_t container_system_get_next(entity_id_t entity)
{
    util_assert(entity_has_component(entity, COMPONENT_CONTAINED));

    return g.contained_components[entity].next;
}

/*
 * @brief Get the entity at a specific position in the container. Position is 1-based index.
 * @param container The ID of the container
 * @param position The 0-based index of the entity in the container
 * @return The ID of the entity at the specified position or ENTITY_ID_INVALID if the position is out of bounds
*/
entity_id_t container_system_get_at(entity_id_t container, uint8_t position)
{
    uint8_t i = 0;
    entity_id_t entity;

    if (container_system_count(container) <= position)
    {
        return ENTITY_ID_INVALID;
    }    

    entity = container_system_get_first(container);

    while (i < position)
    {
        entity = container_system_get_next(entity);
        i++;
    }

    return entity;
}

/*
 * @brief Clean up all entities marked for destruction.
 * @details 
 * If entity is contained then it is removed from the contained list. 
 * If entity is a container then all its contained entities are marked for destruction.
 * @return void
 */
void container_system_clean_up(void)
{
for (entity_id_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (entity_has_flag(i, FLAG_PENDING_DESTORY))
        {
            if (entity_has_component(i, COMPONENT_CONTAINED))
            {
                container_system_remove_item_from(g.contained_components[i].container, i);
            }
            if (entity_has_component(i, COMPONENT_CONTAINER))
            {
                container_system_mark_contents_for_destruction(i);
            }
            entity_mark_for_destruction(i);
        }
    }    
}

/*
 * @brief Remove every item from the container and flag pending destruction
*/
void container_system_mark_contents_for_destruction(entity_id_t container)
{
    entity_id_t entity;

    entity = g.container_components[container].head;

    /* Keep removing items until head is empty */
    while (entity != ENTITY_ID_INVALID)
    {
        container_system_remove_item_from(container, entity);
        entity_mark_for_destruction(entity);

        entity = g.container_components[container].head;
    }

}