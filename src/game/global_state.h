/**
 * @file global_state.h
 * @author Paul Johnson 
 * @brief 
 */

#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "ecs/entity_priv.h"
#include "ecs/components/PAGE50/attack_comp.h"
#include "ecs/components/PAGE50/destructable_comp.h"
#include "ecs/components/PAGE50/item_comp.h"
#include "ecs/components/PAGE50/location_comp.h"
#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/name_comp.h"

#include "ecs/components/PAGE50/creature_comp.h"

#include "ecs/components/PAGE50/container_comp.h"
#include "ecs/components/PAGE50/contained_comp.h"
#include "ecs/components/PAGE50/equippable_comp.h"
#include "ecs/components/PAGE50/equipped_comp.h"

#include "ecs/components/PAGE51/player_comp.h"
#include "ecs/components/PAGE51/renderable_comp.h"
#include "ecs/components/PAGE51/stats_comp.h"
#include "ecs/components/PAGE51/slots_comp.h"
#include "ecs/components/PAGE51/timer_comp.h"

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
    equippable_components_t equippable_components; 
    melee_components_t melee_components; 
    ranged_components_t ranged_components; 
    location_components_t location_components; 
    renderable_components_t renderable_components; 
    creature_components_t creature_components;
    stats_components_t stats_components;
    container_components_t container_components; 
    contained_components_t contained_components; 
    player_comp_t player;
    equipped_components_t equipped_components;
    slots_t slots;
    timer_components_t timer_components; 
    destructable_components_t destructable_components;
    effect_components_t effect_components;
    name_components_t name_components;

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