/**
 * @file location_comp.c
 * @author Paul Johnson
 * @brief location component for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "location_comp.h"

#include "global_state.h"
#include "entity.h"
#include "location_comp_priv.h"
#include "container_comp.h"

#include "map_terrain.h"

#include "util.h"

/***************************************************
 * public functions
 ***************************************************/

void location_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.location_components[i].next_in_location = ENTITY_ID_INVALID; /* clear next in location */
    }

    for (uint8_t x = 0; x < MAP_TERRAIN_WIDTH; x++) {
        for (uint8_t y = 0; y < MAP_TERRAIN_HEIGHT; y++) {
            g.map.cell_head[x][y] = ENTITY_ID_INVALID; /* mark all map cells as empty */
        }
    }
}

bool_t location_add(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_TERRAIN_WIDTH);
    util_assert(y < MAP_TERRAIN_HEIGHT);
    util_assert(!entity_has_component(entity, COMPONENT_LOCATION));  /* entity must not already have a location component */
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINED)); /* entity must not be contained */

    g.location_components[entity].x = x;
    g.location_components[entity].y = y;

    location_link(entity);

    entity_set_component(entity, COMPONENT_LOCATION); /* set entity location component mask */

    return 1; /* success */
}

void location_move(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_TERRAIN_WIDTH);
    util_assert(y < MAP_TERRAIN_WIDTH);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));

    location_unlink(entity);
    g.location_components[entity].x = x;
    g.location_components[entity].y = y;
    location_link(entity);
}

/*
 * @brief Unlink entity from the map and clear its location component
 * @param[in] entity to remove component from
 */
void location_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_component(entity, COMPONENT_LOCATION))
    {
        return;
    }    

    location_unlink(entity);
    entity_clear_component(entity, COMPONENT_LOCATION); /* clear entity location component mask */    
}

/*
 * @brief Link entity to a map cell
 * @param[in] entity to link
 */
void location_link(entity_id_t entity)
{
    uint8_t x = g.location_components[entity].x;
    uint8_t y = g.location_components[entity].y;

    g.location_components[entity].next_in_location = g.map.cell_head[x][y]; /* link to previous head entity at this map cell */
    g.map.cell_head[x][y] = entity; /* set this entity as the head of the list at this map cell */
}

/*
 * @brief Unlink entity from map cell
 * @param[in] entity to unlink
*/
void location_unlink(entity_id_t entity)
{
    entity_id_t x = g.location_components[entity].x;
    entity_id_t y = g.location_components[entity].y;

    /* find entity in cell list */
    entity_id_t current = g.map.cell_head[x][y]; /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                g.map.cell_head[x][y] = g.location_components[current].next_in_location; /* remove from head */
            } else {
                g.location_components[prev].next_in_location = g.location_components[current].next_in_location; /* bypass current */
            }
            return;
        }
        prev = current; 
        current = g.location_components[current].next_in_location; /* move to next */
    }
    util_abort("Entity not found on map");    
}


