 The goal is to include a new function into movement_system.c, called `movement_system_move_to_position`.

The function should move an entity to a specified position on the map, but only if the new position is reachable from the current one.

Here's how you can achieve this:
/**
 * @file movement_system.c
 * @author Paul Johnson
 * @brief movement system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE52/movement_system.h"

#include <stdlib.h>

#include "ecs/components/components.h"
#include "ecs/components/location_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "game/map_terrain.h"
#include "game/map_access.h"

/***************************************************
 * private function prototypes
 ***************************************************/
static void location_move(entity_id_t entity, uint8_t x, uint8_t y);
static void location_link(entity_id_t entity);
static void location_unlink(entity_id_t entity);

/***************************************************
 * public functions
 ***************************************************/
 void movement_system_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.location_components[i].next_in_location = ENTITY_ID_INVALID; /* clear next in location */
    }
}

void movement_system_place(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_WIDTH);
    util_assert(y < MAP_HEIGHT);
    util_assert(!entity_has_component(entity, COMPONENT_LOCATION));  /* entity must not already have a location component */
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINED)); /* entity must not be contained */

    g.location_components[entity].coord.x = x;
    g.location_components[entity].coord.y = y;

    location_link(entity);

    entity_set_component(entity, COMPONENT_LOCATION); /* set entity location component mask */
}

bool movement_system_try_move(entity_id_t actor, int8_t dx, int8_t dy)
 {
    uint8_t tx;
    uint8_t ty;

    if ((dx == 0) && (dy == 0))
        return 0;

    tx = g.location_components[actor].coord.x + dx;
    ty = g.location_components[actor].coord.y + dy;

    if (map_can_enter(tx, ty))
    {
        location_move(actor, tx, ty);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool movement_system_try_move_random(entity_id_t actor)
 {
    direction_t dir;
    
    dir = (rand() % 4) + 1; /* random direction */

    return movement_system_try_move(actor, directions[dir].x, directions[dir].y);
}

bool movement_system_try_move_towards(entity_id_t entity, coord_t *coord)
{
coord_t *m = &g.location_components[entity].coord;
    

    /* Determine chase direction */
    int8_t dx = 0;
    int8_t dy = 0; 

    if (coord->x > m->x) dx = 1;
    else if (coord->x < m->x) dx = -1;

    if (coord->y > m->y) dy = 1;
    else if (coord->y < m->y) dy = -1;

    /* No move needed */
    if ((dx == 0) && (dy == 0))
        return 0;

    /* Try direct move */
    if (movement_system_try_move(entity, dx, dy))
        return 1;

    /* Try axis-only fallback */
    if (dx && movement_system_try_move(entity, dx, 0))
        return 1;

    if (dy && movement_system_try_move(entity, 0, dy))
        return 1;

    /* Try small sidestep to avoid obstacles */
    static const int8_t sidestep[4][2] = {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
    };

    for (uint8_t i = 0; i < 4; i++)
    {
        if (movement_system_try_move(entity, sidestep[i][0], sidestep[i][1]))
            return 1;
    }

    /* Can't move anywhere useful */
    return 0;
}

/*
 * @brief Unlink entity from the map and remove its location component
 * @param[in] entity to remove component from
 */
void movement_system_detach(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_component(entity, COMPONENT_LOCATION))
    {
        return;
    }    

    location_unlink(entity);
    entity_clear_component(entity, COMPONENT_LOCATION); /* clear entity location component mask */    
}

bool movement_system_location_equal(entity_id_t entity1, entity_id_t entity2)
{
    util_assert(entity1 < MAX_ENTITIES);
    util_assert(entity2 < MAX_ENTITIES);
    util_assert(entity_has_component(entity1, COMPONENT_LOCATION));
    util_assert(entity_has_component(entity2, COMPONENT_LOCATION));

    return coord_equal(g.location_components[entity1].coord, g.location_components[entity2].coord);
}

bool movement_system_are_adjacent(entity_id_t entity1, entity_id_t entity2)
{
    util_assert(entity1 < MAX_ENTITIES);
    util_assert(entity2 < MAX_ENTITIES);
    util_assert(entity_has_component(entity1, COMPONENT_LOCATION));
    util_assert(entity_has_component(entity2, COMPONENT_LOCATION));

    return are_adjacent(g.location_components[entity1].coord, g.location_components[entity2].coord);
}

 /***************************************************
 * private functions
 ***************************************************/

static void location_move(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(x < MAP_WIDTH);
    util_assert(y < MAP_WIDTH);
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));

    location_unlink(entity);
    g.location_components[entity].coord.x = x;
    g.location_components[entity].coord.y = y;
    location_link(entity);
}

/*
 * @brief Link entity to a map cell
 * @param[in] entity to link
 */
static void location_link(entity_id_t entity)
{
    uint8_t x = g.location_components[entity].coord.x;
    uint8_t y = g.location_components[entity].coord.y;

    /* Mark map window as dirty*/
    g.main_win.dirty = 1;

    g.location_components[entity].next_in_location = map_get_first(x, y); /* link to previous head entity at this map cell */
    map_set_entity_head(x, y, entity); /* set this entity as the head of the list at this map cell */
}

/*
 * @brief Unlink entity from map cell
 * @param[in] entity to unlink
*/
static void location_unlink(entity_id_t entity)
{
    entity_id_t x = g.location_components[entity].coord.x;
    entity_id_t y = g.location_components[entity].coord.y;

    /* Mark map window as dirty*/
    g.main_win.dirty = 1;

    /* find entity in cell list */
    entity_id_t current = map_get_first(x, y); /* start at the head of the list */
    entity_id_t prev = ENTITY_ID_INVALID; /* previous entity in the list */

    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) {
                map_set_entity_head(x, y, g.location_components[current].next_in_location); /* remove from head */
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