/**
 * @file actions_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "actions_system.h"

#include "ecs/entity.h"

#include "ecs/components/PAGE50/equippable_comp.h"
#include "ecs/components/PAGE50/equipped_comp.h"
#include "ecs/components/PAGE51/slots_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/game.h"
#include "game/global_state.h"

#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/

 /***************************************************
 * private function prototypes
 ***************************************************/
 int8_t calc_attack_roll(entity_id_t attacker, attack_type_t attack_type);

/***************************************************
 * public functions
 ***************************************************/
void actions_system_init(void)
{
}

 bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature)
{
    
}



bool_t actions_system_try_eat(entity_id_t actor, entity_id_t item)
{

}

bool_t actions_system_try_open(entity_id_t actor, entity_id_t feature)
{

}

bool_t actions_system_try_quaff(entity_id_t actor, entity_id_t item)
 {

 }

