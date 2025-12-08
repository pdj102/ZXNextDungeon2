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
#include "ecs/entity_priv.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/item_comp.h"
#include "ecs/components/location_comp_priv.h"
#include "ecs/components/renderable_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/container_comp.h"
#include "ecs/components/contained_comp.h"
#include "ecs/components/player_ctrl_comp_priv.h"
#include "ecs/components/timer_comp_priv.h"

#include "../game/map_priv.h"

#include "core/text.h"

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
    equip_components_t equip_components; /* equipable component data */
    melee_components_t melee_components; /* melee attack component data */
    ranged_components_t ranged_components; /* ranged attack component data */

    location_components_t location_components; /* location component data */
    renderable_components_t renderable_components; /* sprite component data */

    creature_components_t creature_components;
    creature_stats_components_t creature_stat_components;

    container_components_t container_components; /* container component data */
    contained_components_t contained_components; /* contained component data */
    player_ctrl_comp_t player; /* player component data */
    timer_components_t timer_components; /* timer component data */

    /* World */
    map_t map; /* the map */

    /* UI */
    text_window_t stat_win;
    text_window_t msg_win;
    text_window_t main_win;
    text_window_t assert_win;


} global_state_t;


/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */