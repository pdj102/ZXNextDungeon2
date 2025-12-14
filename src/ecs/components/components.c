/**
 * @file components.c
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/components.h"

 #include <arch/zxn.h>

#include "ecs/entity.h"

#include "ecs/components/attack_comp.h"
#include "ecs/components/contained_comp.h"
#include "ecs/components/container_comp.h"
#include "ecs/components/equippable_comp.h"
#include "ecs/components/equipped_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/item_comp.h"
#include "ecs/components/location_comp.h"
#include "ecs/components/player_comp.h"
#include "ecs/components/renderable_comp.h"
#include "ecs/components/slots_comp.h"
#include "ecs/components/stats_comp.h"
#include "ecs/components/timer_comp.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void components_init(void)
{
    attack_init();
    contained_init();
    container_init();
    creature_init();
    equippable_init();
    equipped_init();
    item_init();
    location_init();
    player_init();
    renderable_init();
    slots_init();
    stats_init();
    timer_init();
}

 /***************************************************
 * private functions
 ***************************************************/