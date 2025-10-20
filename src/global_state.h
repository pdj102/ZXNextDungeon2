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
#include "contained_comp_priv.h"
#include "player_ctrl_comp_priv.h"

#include "map_priv.h"
#include "map_terrain_priv.h"

#include "text.h"

/***************************************************
 * public defines
 ***************************************************/
#define GLOBAL_STATE_BASE_ADDRESS 0x0000

/***************************************************
 * public types
 * ***************************************************/
typedef struct 
{
    /* ECS */
    entity_components_t entity_components; /* entity data */
    item_components_t item_components; /* item component data */
    location_components_t location_components; /* location component data */
    sprite_components_t sprite_components; /* sprite component data */
    creature_components_t creature_components; /* creature component data */
    container_components_t container_components; /* container component data */
    contained_components_t contained_components; /* contained component data */
    player_ctrl_comp_t player; /* player component data */

    /* World */
    map_t map; /* the map */

    /* UI */
    text_window_t stat_win;      
    text_window_t msg_win;  


} global_state_t;


/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */

