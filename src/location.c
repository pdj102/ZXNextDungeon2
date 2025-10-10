/**
 * @file location.c
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "location.h"

#include "global_state.h"

#include "entity.h"
#include "map.h"

#include "util.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

 /***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/

void place_on_map(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_WIDTH);
    util_assert(y < MAP_HEIGHT);
    util_assert(g.location[entity].type == LOC_NONE); /* entity must not be placed */

    // remove_from_current_location(entity); /* remove from current location if any */

    g.location[entity].type = LOC_MAP;
    g.location[entity].data.map.x = x;
    g.location[entity].data.map.y = y;
    g.location[entity].next_in_location = g.location_cell_head[x][y]; /* link to previous head entity at this map cell */
    g.location_cell_head[x][y] = entity; /* set this entity as the head of the list at this map cell */
}

void put_in_container(entity_id_t entity, entity_id_t container) {
    
    util_assert(entity < MAX_ENTITIES);
    util_assert(container < MAX_ENTITIES);
    util_assert(g.location[entity].type == LOC_NONE); /* entity must not be placed */

    // remove_from_current_location(entity); /* remove from current location if any */

    g.location[entity].type = LOC_CONTAINER;
    g.location[entity].data.container = container;

    g.location[entity].next_in_location = g.location_container_head[container]; /* link to previous head entity in this container */
    g.location_container_head[container] = entity; /* set this entity as the head of the list in this container */
}


void remove_from_map(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.location[entity].type == LOC_MAP);

    entity_id_t x = g.location[entity].data.map.x;
    entity_id_t y = g.location[entity].data.map.y;
    entity_id_t current = g.location_cell_head[x][y]; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.location_cell_head[x][y] = g.location[current].next_in_location; /* remove from head */
            } else {
                g.location[prev].next_in_location = g.location[current].next_in_location; /* bypass current */
            }
            g.location[current].type = LOC_NONE; /* mark as not placed */
            g.location[current].next_in_location = ENTITY_ID_INVALID; /* clear next */
            return;
        }
        prev = current; 
        current = g.location[current].next_in_location; /* move to next */
    }
    util_abort("Entity not found on map");
}

void remove_from_container(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.location[entity].type == LOC_CONTAINER);

    entity_id_t container = g.location[entity].data.container;
    entity_id_t current = g.location_container_head[container]; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.location_container_head[container] = g.location[current].next_in_location; /* remove from head */
            } else {
                g.location[prev].next_in_location = g.location[current].next_in_location; /* bypass current */
            }
            g.location[current].type = LOC_NONE; /* mark as not placed */
            g.location[current].next_in_location = ENTITY_ID_INVALID; /* clear next */
            return;
        }
        prev = current; 
        current = g.location[current].next_in_location; /* move to next */
    }
    util_abort("Entity not found in container");
}

void remove_from_current_location(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    switch (g.location[entity].type) {
        case LOC_MAP:
            remove_from_map(entity);
            break;
        case LOC_CONTAINER:
            remove_from_container(entity);
            break;
        case LOC_NONE:
            // Entity is not placed, nothing to do
            break;
        default:
            util_abort("Invalid location type");
    }
}
