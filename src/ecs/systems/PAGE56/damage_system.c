/**
 * @file damage_system.c
 * @author Paul Johnson
 * @brief damage system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE56/damage_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private function prototypes
 ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
bool_t damage_system_try_die(entity_id_t creature)
{
    if (!entity_has_component(creature, COMPONENT_CREATURE))
    {
        return 0;
    }

    system_event_emit(EVENT_DIED, creature, ENTITY_ID_INVALID, 0);

    g.creature_components[creature].status = CREATURE_STATUS_DEAD;
    entity_mark_for_destruction(creature);

    return 1;
}

int8_t damage_system_try_take_damage(entity_id_t actor, int8_t damage, damage_type_t type)
{
    if (!entity_has_component(actor, COMPONENT_STATS | COMPONENT_CREATURE))
    {
        return 0;
    }

    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.stats_components[actor].cur_hp <= damage)
    {
        g.stats_components[actor].cur_hp = 0;
        damage_system_try_die(actor);
    }
    else
    {
        g.stats_components[actor].cur_hp -= damage;
    }
    
    return damage;
}
 
 /***************************************************
 * private functions
 ***************************************************/
