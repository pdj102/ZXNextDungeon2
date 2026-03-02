/**
 * @file container_system.c
 * @author Paul Johnson
 * @brief A container can contain items. Contained items have a contained component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "container_system.h"

#include <stdbool.h>

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
 static entity_id_t find_matching_stackable(entity_id_t container, name_id_t name);

/***************************************************
 * public functions
 ***************************************************/
void container_system_init(void)
{

}


bool container_system_try_pickup(entity_id_t actor, entity_id_t item)
{
    event_t event;
    entity_id_t existing;

    /* Item must be pickable and on the floor */
    if (!entity_has_component(item, COMPONENT_PICKABLE))
    {
        return 0;
    }
    if (!entity_has_component(item, COMPONENT_LOCATION))
    {
        return 0;
    }
    /* Actor must be a container with a location */
    if (!entity_has_component(actor, COMPONENT_CONTAINER))
    {
        return 0;
    }
    if (!entity_has_component(actor, COMPONENT_LOCATION))
    {
        return 0;
    }
    /* Actor and item are at the same location */
    if (!system_movement_location_equal(actor, item))
    {
        return 0;
    }

    /* Try to merge with an existing stack (bypasses capacity check) */
    if (entity_has_component(item, COMPONENT_STACKABLE))
    {
        existing = find_matching_stackable(actor, g.name_components[item]);
        if (existing != ENTITY_ID_INVALID)
        {
            system_movement_detach(item);
            g.stackable_components[existing].quantity += g.stackable_components[item].quantity;
            entity_mark_for_destruction(item);

            event.type   = EVENT_PICKED_UP;
            event.source = actor;
            event.target = existing;
            event.value  = 0;
            system_event_emit(&event);
            return 1;
        }
    }

    /* No matching stack — need a free slot */
    if (g.container_components[actor].count >= g.container_components[actor].capacity)
    {
        return 0;
    }

    /* Remove item from floor */
    system_movement_detach(item);

    /* Place item in container */
    container_system_add(actor, item);

    event.type   = EVENT_PICKED_UP;
    event.source = actor;
    event.target = item;
    event.value  = 0;
    system_event_emit(&event);
    return 1;
}

bool container_system_try_drop(entity_id_t actor, entity_id_t item)
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
    container_system_remove(item);
    
    /* Place item on the floor*/
    system_movement_place(item, g.location_components[actor].coord.x, g.location_components[actor].coord.y);

    event.type = EVENT_DROPPED;
    event.source = actor;
    event.target = item;
    event.value = 0;

    system_event_emit(&event);

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


void container_system_remove(entity_id_t item)
{
    entity_id_t container;

    util_assert(item < MAX_ENTITIES);
    util_assert(entity_has_component(item, COMPONENT_CONTAINED));

    container = g.contained_components[item].container;
    util_assert(container < MAX_ENTITIES);
 
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
 * @brief Get the entity at a specific position in the container using 0-based indexing.
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
        container_system_remove(id);
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
        container_system_remove(entity);
        /* Mark for destruction */
        entity_mark_for_destruction(entity);

        entity = g.container_components[container].head;
    }
}

/*
 * @brief Check if entity is protected by persistence flag
 * @details Returns true if the entity or any container in its chain has FLAG_PERSISTANT.
 *          Traverses up the container hierarchy to check for persistence protection.
 * @param id Identity of the entity to check
 * @return true if entity is protected by persistence, false otherwise
 */
bool container_system_is_protected_by_persistence(entity_id_t id)
{
    entity_id_t cur = id;

    while (cur != ENTITY_ID_INVALID)
    {
        if (entity_has_flag(cur, FLAG_PERSISTANT))
            return true;

        if (!entity_has_component(cur, COMPONENT_CONTAINED))
            break;

        cur = g.contained_components[cur].container;
    }

    return false;
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

/*
 * @brief Find an existing stackable item in a container with a matching name_id.
 * @param container The container to search.
 * @param name      The name_id to match against.
 * @return The matching entity, or ENTITY_ID_INVALID if none found.
 */
static entity_id_t find_matching_stackable(entity_id_t container, name_id_t name)
{
    entity_id_t current = g.container_components[container].head;
    while (current != ENTITY_ID_INVALID)
    {
        if (entity_has_component(current, COMPONENT_STACKABLE) &&
            g.name_components[current] == name)
        {
            return current;
        }
        current = g.contained_components[current].next;
    }
    return ENTITY_ID_INVALID;
}