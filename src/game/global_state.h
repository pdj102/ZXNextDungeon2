/**
 * @file global_state.h
 * @author Paul Johnson 
 * @brief 
 */

#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "ecs/entity_priv.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/item_comp.h"
#include "ecs/components/location_comp.h"
#include "ecs/components/renderable_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/stats_comp.h"
#include "ecs/components/container_comp.h"
#include "ecs/components/contained_comp.h"
#include "ecs/components/equip_comp.h"
#include "ecs/components/equipable_comp.h"
#include "ecs/components/player_comp.h"
#include "ecs/components/timer_comp_priv.h"

#include "game/map_priv.h"

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
    entity_components_t entity_components; 
    item_components_t item_components; 
    equipable_components_t equipable_components; 
    melee_components_t melee_components; 
    ranged_components_t ranged_components; 
    location_components_t location_components; 
    renderable_components_t renderable_components; 
    creature_components_t creature_components;
    stats_components_t stats_components;
    container_components_t container_components; 
    contained_components_t contained_components; 
    player_comp_t player;
    equip_slots_t equip_slots; 
    timer_components_t timer_components; 

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