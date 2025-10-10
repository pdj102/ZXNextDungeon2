/**
 * @file global_state.h
 * @author Paul Johnson 
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H


#include "entity_priv.h"
#include "item_priv.h"
#include "location.h"

#include "map.h"

/***************************************************
 * public defines
 ***************************************************/
#define GLOBAL_STATE_BASE_ADDRESS 0x0000

/***************************************************
 * public types
 * ***************************************************/
typedef struct 
{
    /* ECS - Entity */
    entity_arena_t entity_arena; /* entity arena */
    /* ECS - Item */
    item_component_t item_components[MAX_ENTITIES]; /* item component data per entity */
    /* ECS - Location */
    location_t location[MAX_ENTITIES]; /* location data per entity */
    entity_id_t location_cell_head[MAP_WIDTH][MAP_HEIGHT]; /* linked list head for entities at each map cell */
    entity_id_t location_container_head[MAX_ENTITIES]; /* linked list head for entities in each container */
} global_state_t;


/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */

