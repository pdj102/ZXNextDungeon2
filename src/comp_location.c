/**
 * @file comp_location.c
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "comp_location.h"

#include "entity.h"

#include "util.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

typedef enum {
    LOC_NONE,       // entity is not placed
    LOC_MAP,        // entity is on the map
    LOC_ENTITY      // entity is contained in another entity
} location_type_t;

typedef struct {
    location_type_t type;   /* type of location */
    union {
        struct {
            uint8_t  x; /* x coordinate on the map */
            uint8_t; /* y coordinate on the map */
        } map;
        entity_id_t container; /* entity containing this entity */
    } data;
    entity_id_t next_in_container; /* next entity in the same container or next entity at map cell */
} location_t;

 /***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

static location_t locations[MAX_ENTITIES]; /* location data per entity */

static entity_id_t map[MAP_WIDTH][MAP_HEIGHT]; /* linked list of entities at each map cell */

/***************************************************
 * public functions
 ***************************************************/

void place_on_map(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert(entity < MAX_ENTITIES);

    locations[entity].type = LOC_MAP;
    locations[entity].data.map.x = x;
    locations[entity].data.map.y = y;
    locations[entity].next_in_container = map[x][y]; /* link to previous entity at this map cell */
    map[x][y] = entity; /* set this entity as the head of the list at this map cell */
}

void remove_from_map(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(locations[entity].type == LOC_MAP);

    entity_id_t x = locations[entity].data.map.x;
    entity_id_t y = locations[entity].data.map.y;
    entity_id_t *head = &map[x][y];
    entity_id_t current = *head;
    entity_id_t prev = ENTITY_ID_INVALID;
    while (current != ENTITY_ID_INVALID) { /* traverse the linked list */
        if (current == entity) { /* found the entity to remove */
            if (prev == ENTITY_ID_INVALID) { 
                *head = locations[current].next_in_container; /* remove from head */
            } else {
                locations[prev].next_in_container = locations[current].next_in_container; /* bypass current */
            }
            locations[current].type = LOC_NONE; /* mark as not placed */
            locations[current].next_in_container = ENTITY_ID_INVALID; /* clear next */
            return;
        }
        prev = current; 
        current = locations[current].next_in_container; /* move to next */
    }
    util_abort("Entity not found on map");
}


