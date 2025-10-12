/**
 * @file location_comp.c
 * @author Paul Johnson
 * @brief location management for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "location_comp.h"

#include "global_state.h"
#include "entity.h"
#include "location_comp_priv.h"

#include "terrain_map.h"

#include "util.h"

/***************************************************
 * public functions
 ***************************************************/

void location_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.location_components[i].type = LOC_NONE; /* mark all entities as not placed */
        g.location_components[i].next_in_location = ENTITY_ID_INVALID; /* clear next in location */
    }

    for (uint8_t x = 0; x < TERRAIN_MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < TERRAIN_MAP_HEIGHT; y++) {
            g.location_cell_head[x][y] = ENTITY_ID_INVALID; /* mark all map cells as empty */
        }
    }

    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        g.location_container_head[i] = ENTITY_ID_INVALID; /* mark all containers as empty */
    }
}

bool_t location_init_for_entity(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    g.location_components[entity].type = LOC_NONE; /* mark as not placed */
    g.location_components[entity].next_in_location = ENTITY_ID_INVALID; /* clear next in location */

    entity_set_component(entity, COMPONENT_LOCATION); /* set entity location component mask */

    return 1; /* success */
}

void location_place_on_map(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(x < TERRAIN_MAP_WIDTH);
    util_assert(y < TERRAIN_MAP_HEIGHT);
    util_assert(g.location_components[entity].type == LOC_NONE); /* entity must not be placed */

    g.location_components[entity].type = LOC_MAP;
    g.location_components[entity].data.map.x = x;
    g.location_components[entity].data.map.y = y;
    g.location_components[entity].next_in_location = g.location_cell_head[x][y]; /* link to previous head entity at this map cell */
    g.location_cell_head[x][y] = entity; /* set this entity as the head of the list at this map cell */
}

void location_put_in_container(entity_id_t entity, entity_id_t container) {
    
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(container < MAX_ENTITIES);
    // todo implement container_components and check entity is a container
    util_assert(g.location_components[entity].type == LOC_NONE); /* entity must not be placed */

    g.location_components[entity].type = LOC_CONTAINER;
    g.location_components[entity].data.container = container;

    g.location_components[entity].next_in_location = g.location_container_head[container]; /* link to previous head entity in this container */
    g.location_container_head[container] = entity; /* set this entity as the head of the list in this container */
}

void location_remove_from_map(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(g.location_components[entity].type == LOC_MAP);

    entity_id_t x = g.location_components[entity].data.map.x;
    entity_id_t y = g.location_components[entity].data.map.y;
    entity_id_t current = g.location_cell_head[x][y]; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.location_cell_head[x][y] = g.location_components[current].next_in_location; /* remove from head */
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
    util_abort("Entity not found on map");
}

void location_remove_from_container(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(g.location_components[entity].type == LOC_CONTAINER);

    entity_id_t container = g.location_components[entity].data.container;
    entity_id_t current = g.location_container_head[container]; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.location_container_head[container] = g.location_components[current].next_in_location; /* remove from head */
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

void location_remove_from_current(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));

    switch (g.location_components[entity].type) {
        case LOC_MAP:
            location_remove_from_map(entity);
            break;
        case LOC_CONTAINER:
            location_remove_from_container(entity);
            break;
        case LOC_NONE:
            // Entity is not placed, nothing to do
            break;
        default:
            util_abort("Invalid location type");
    }
}

void location_destroy(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);

    location_remove_from_current(id); /* remove from current location if placed */

    g.location_components[id].type = LOC_NONE; /* mark as not placed */
    g.location_components[id].next_in_location = ENTITY_ID_INVALID; /* clear next */

    entity_clear_component(id, COMPONENT_LOCATION); /* clear entity location component mask */
}
