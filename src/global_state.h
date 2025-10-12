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


/* Special case - include private headers to define the global game state structure */
#include "entity_priv.h"
#include "item_comp_priv.h"
#include "location_comp_priv.h"
#include "sprite_comp_priv.h"
#include "creature_comp_priv.h"

#include "terrain_map_priv.h"

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
    item_comp_t item_components[MAX_ENTITIES]; /* item component data per entity */
    /* ECS - Location */
    location_comp_t location_components[MAX_ENTITIES]; /* location component data per entity */
    entity_id_t location_cell_head[TERRAIN_MAP_WIDTH][TERRAIN_MAP_HEIGHT]; /* linked list head for entities at each terrain_map cell */
    entity_id_t location_container_head[MAX_ENTITIES]; /* linked list head for entities in each container */
    /* ECS - Sprite*/
    sprite_comp_t sprite_components[MAX_ENTITIES]; /* sprite component data per entity*/
    /* ECS - Creature*/
    creature_comp_t creature_components[MAX_ENTITIES]; /* creature component data per entity */

    /* Terrain_map */
    terrain_map_t terrain_map; /* the game terrain_map */

} global_state_t;


/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */

