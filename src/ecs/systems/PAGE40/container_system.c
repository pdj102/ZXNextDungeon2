/**
 * @file container_system.c
 * @author Paul Johnson
 * @brief A container can contain items. Contained items have a contained component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "container_system.h"

#include <sys\types.h>

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "ecs/components/container_comp.h"
#include "ecs/components/contained_comp.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "core/util.h"
#include "game/global_state.h"

/***************************************************
 * private variables
 ****************************************************/

/***************************************************
 * private functions
 ****************************************************/
 static void contained_add(entity_id_t entity, entity_id_t container, entity_id_t next);
 static void contained_remove(entity_id_t entity);

/***************************************************
 * public functions
 ***************************************************/
void container_system_init(void)
{

}


bool_t container_system_try_pickup(entity_id_t actor, entity_id_t item)
{  
    event_t event;

    /* item to be picked up has item and location components */
    if (!entity_has_component(item, COMPONENT_ITEM))
    {
        return 0;
    }
    if (!entity_has_component(item, COMPONENT_LOCATION))
    {
        return 0;
    }    
    /* actor has container, location and item components */
    if (!entity_has_component(actor, COMPONENT_CONTAINER))
    {
        return 0;
    }    
    if (!entity_has_component(actor, COMPONENT_LOCATION ))
    {
        return 0;
    }        
    /* actor and item are at the same location*/
    if (!system_movement_location_equal(actor, item))
    {
        return 0;
    }
    /* container is not full */
    if (g.container_components[actor].count >= g.container_components[actor].capacity)
    {
        return 0;
    }    

    /* Remove item from floor */
    system_movement_cleanup(item);

    /* Place item in container */
    container_system_add(actor, item);

    event.type = EVENT_PICKED_UP;
    event.source = actor;
    event.target = item;
    event.value = 0;

    system_event_emit(event);

    return 1;
}

bool_t container_system_try_drop(entity_id_t actor, entity_id_t item)
{
    event_t event;

    /* check item to be droped is contained  */
    if (!entity_has_component(item, COMPONENT_CONTAINED))
    {
        return 0;
    }    
    /* check actor has container */
    if (!entity_has_component(actor, COMPONENT_CONTAINER))
    {
        return 0;
    }
    /* check actor has location */
    if (!entity_has_component(actor, COMPONENT_LOCATION))
    {
        return 0;
    }    
    /* check actor is holding the item */
    if (g.contained_components[item].container != actor)
    {
        return 0;
    }

    /* check - can't drop equipped items */
    if (system_equipment_is_equipped(actor, item) == 1)
    {
        return 0;
    }

    /* Remove item from container */
    container_system_remove(actor, item);
    
    /* Place item on the floor*/
    system_movement_place(item, g.location_components[actor].x, g.location_components[actor].y);

    event.type = EVENT_DROPPED;
    event.source = actor;
    event.target = item;
    event.value = 0;

    system_event_emit(event);

    return 1;
}

void container_system_add(entity_id_t container, entity_id_t item)
{
    util_assert(item < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(!entity_has_component(item, COMPONENT_CONTAINED)); /* must not already be contained */
    util_assert(!entity_has_component(item, COMPONENT_LOCATION)); /* must not be placed on the map */

    /* Add contained component */
    /* Contained item holds a reference to container */
    /* Set next to current container head */
    contained_add(item, container, g.container_components[container].head);

    g.container_components[container].head = item; /* set container head to entity */
    g.container_components[container].count++;
}


void container_system_remove(entity_id_t container, entity_id_t item)
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
 * @param index The 0-based index of the entity in the container
 * @return The ID of the entity at the specified position or ENTITY_ID_INVALID if the position is out of bounds
*/
entity_id_t container_system_get_at(entity_id_t container, uint8_t index)
{
    uint8_t i = 0;
    entity_id_t entity;

    if (container_system_count(container) <= index)
    {
        return ENTITY_ID_INVALID;
    }    

    entity = container_system_get_first(container);

    while (i < index)
    {
        entity = container_system_get_next(entity);
        i++;
    }

    return entity;
}

/*
 * @brief Clean up an entity marked for destruction.
 * @details 
 * If entity is contained then it is removed from the container
 * If entity is a container then all its contained entities are removed and marked for destruction.
 * 
 * @param id Identity of the entity to be cleaned up. 
 */
void container_system_clean_up(entity_id_t id)
{
    if (entity_has_component(id, COMPONENT_CONTAINED))
    {
        container_system_remove(g.contained_components[id].container, id);
    }
    if (entity_has_component(id, COMPONENT_CONTAINER))
    {
        container_system_mark_contents_for_destruction(id);
    }
}

/*
 * @brief Remove every item from a container and flag pending destruction
*/
void container_system_mark_contents_for_destruction(entity_id_t container)
{
    entity_id_t entity;

    entity = g.container_components[container].head;

    /* Keep removing items until head is empty */
    while (entity != ENTITY_ID_INVALID)
    {
        container_system_remove(container, entity);
        entity_mark_for_destruction(entity);

        entity = g.container_components[container].head;
    }
}

/***************************************************
 * private functions
 ****************************************************/

/*
 * @brief Add a contained component to the entity and place the entity in the container entity e.g. add potion (item) to chest (container)
 */
static void contained_add(entity_id_t entity, entity_id_t container, entity_id_t next)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINED)); /* entity must not have contained component */
    util_assert(!entity_has_component(entity, COMPONENT_LOCATION)); /* entity must not have location component */

    g.contained_components[entity].container = container;
    g.contained_components[entity].next = next;

    entity_set_component(entity, COMPONENT_CONTAINED); /* set entity contained component mask */    
}

/*
 * @brief Remove the contained entity from its container and remove its contained component e.g. remove potion (item) from a chest (container)
*/
static void contained_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.contained_components[entity].container == ENTITY_ID_INVALID); /* entity must not be in a container */

    entity_clear_component(entity, COMPONENT_CONTAINED);
}