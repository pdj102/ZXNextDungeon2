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
#include "ecs/components/PAGE50/slots_comp.h"

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

bool_t actions_system_try_die(entity_id_t creature)
{
    system_event_emit(EVENT_DIED, creature, ENTITY_ID_INVALID, 0);

    entity_mark_for_destruction(creature);

    return 1;
}

bool_t actions_system_try_eat(entity_id_t actor, entity_id_t item)
{

}




int8_t actions_system_try_take_damage(entity_id_t actor, int8_t damage, damage_type_t type)
{
    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.stats_components[actor].cur_hp <= damage)
    {
        g.stats_components[actor].cur_hp = 0;
        actions_system_try_die(actor);
    }
    else
    {
        g.stats_components[actor].cur_hp -= damage;
    }
    
    return damage;
}

bool_t actions_system_try_open(entity_id_t actor, entity_id_t feature)
{

}

bool_t actions_system_try_quaff(entity_id_t actor, entity_id_t item)
 {

 }

