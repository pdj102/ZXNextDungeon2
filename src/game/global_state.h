/**
 * @file global_state.h
 * @author Paul Johnson 
 * @brief 
 */

#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include "ecs/entity_priv.h"

#include "ecs/components/ai_comp.h"
#include "ecs/components/active_effect_comp.h"
#include "ecs/components/ammo_comp.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/container_comp.h"
#include "ecs/components/contained_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/destructible_comp.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/equippable_comp.h"
#include "ecs/components/equipped_comp.h"
#include "ecs/components/location_comp.h"
#include "ecs/components/name_comp.h"
#include "ecs/components/openable_comp.h"
#include "ecs/components/player_comp.h"
#include "ecs/components/renderable_comp.h"
#include "ecs/components/stackable_comp.h"
#include "ecs/components/stats_comp.h"
#include "ecs/components/slots_comp.h"
#include "ecs/components/timer_comp.h"
#include "ecs/components/transition_com.h"

#include "game/map_priv.h"
#include "game/camera.h"

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
    stackable_components_t stackable_components; 
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
    destructible_components_t destructible_components;
    effect_components_t effect_components;
    name_components_t name_components;
    ai_components_t ai_components;
    ammo_components_t ammo_components;
    openable_components_t openable_components;
    transition_components_t transition_components;

    active_effect_components_t* active_effect_components; /* Pointer to active effects component array in PAGE 60 */

    /* World */
    uint8_t depth;
    map_t map; 
    camera_t camera;

    /* UI */
    text_window_t stat_win;
    text_window_t msg_win;
    text_window_t main_win;
    text_window_t info_win;
    text_window_t assert_win;

} global_state_t;



/***************************************************
 * public variables
 * ***************************************************/

  __at (0x0000) static global_state_t g; /* global state */
 
#endif /* GLOBAL_STATE_H */