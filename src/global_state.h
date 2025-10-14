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
#include "container_comp_priv.h"
#include "player_ctrl_comp_priv.h"

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
    entity_components_t entity_components; /* entity arena */
    /* ECS - Item */
    item_components_t item_components; /* item component data */
    /* ECS - Location */
    location_components_t location_components; /* location component data */
    /* ECS - Sprite*/
    sprite_components_t sprite_components; /* sprite component data */
    /* ECS - Creature*/
    creature_components_t creature_components; /* creature component data */
    /* ECS - Container */
    container_components_t container_components; /* container component data */
    /* ECS - Player */
    player_ctrl_comp_t player; /* the player component*/

    /* Terrain_map */
    terrain_map_t terrain_map; /* the game terrain_map */
    entity_id_t location_cell_head[TERRAIN_MAP_WIDTH][TERRAIN_MAP_HEIGHT]; /* linked list head for entities at each terrain_map cell */


    
} global_state_t;


/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */

