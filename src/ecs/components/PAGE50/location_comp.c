/**
 * @file location_comp.c
 * @author Paul Johnson
 * @brief location component for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/location_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private function prototypes
 ***************************************************/
void location_unlink(entity_id_t entity);
void location_link(entity_id_t entity);

/***************************************************
 * public functions
 ***************************************************/

void location_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.location_components[i].next_in_location = ENTITY_ID_INVALID; /* clear next in location */
    }
}

void location_add(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_WIDTH);
    util_assert(y < MAP_HEIGHT);
    util_assert(!entity_has_components(entity, COMPONENT_LOCATION));  /* entity must not already have a location component */
    util_assert(!entity_has_components(entity, COMPONENT_CONTAINED)); /* entity must not be contained */

    g.location_components[entity].x = x;
    g.location_components[entity].y = y;

    location_link(entity);

    entity_set_component(entity, COMPONENT_LOCATION); /* set entity location component mask */
}

void location_move(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_WIDTH);
    util_assert(y < MAP_WIDTH);
    util_assert(entity_has_components(entity, COMPONENT_LOCATION));

    location_unlink(entity);
    g.location_components[entity].x = x;
    g.location_components[entity].y = y;
    location_link(entity);
}

bool_t location_equal(entity_id_t entity1, entity_id_t entity2)
{
    util_assert(entity1 < MAX_ENTITIES);
    util_assert(entity2 < MAX_ENTITIES);
    util_assert(entity_has_components(entity1, COMPONENT_LOCATION));
    util_assert(entity_has_components(entity2, COMPONENT_LOCATION));

    if ((g.location_components[entity1].x == g.location_components[entity2].x) &&
        (g.location_components[entity1].y == g.location_components[entity2].y))
    {
        return 1;
    }
    return 0;
}

/*
 * @brief Unlink entity from the map and remove its location component
 * @param[in] entity to remove component from
 */
void location_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_components(entity, COMPONENT_LOCATION))
    {
        return;
    }    

    location_unlink(entity);
    entity_clear_component(entity, COMPONENT_LOCATION); /* clear entity location component mask */    
}

 /***************************************************
 * private functions
 ***************************************************/

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


