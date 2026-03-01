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
 * private defines
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static bool damage_type_immune(entity_id_t actor, damage_flag_t type);
static bool damage_type_resistant(entity_id_t actor, damage_flag_t type);
static bool damage_type_vulnerable(entity_id_t actor, damage_flag_t type);

/***************************************************
 * public functions
 ***************************************************/
bool damage_system_try_kill(entity_id_t target, entity_id_t source)
{
    event_t event;

    if (entity_has_component(target, COMPONENT_DESTRUCTIBLE))
    {
        g.destructible_components[target].cur_hp = 0;
    }

    entity_mark_for_destruction(target);

    event.type = EVENT_KILLED;
    event.source = source;
    event.target = target;
    event.value = 0;
    system_event_emit(&event);
    return 1;
}

int8_t damage_system_try_take_damage(entity_id_t target, entity_id_t source, int8_t damage, damage_flag_t flag)
{
    event_t event;

    event.type = EVENT_DAMAGED;

    if (!entity_has_component(target, COMPONENT_DESTRUCTIBLE ))
    {
        return 0;
    }

    /* TODO: Implement checking damage is above threshold*/
    /* if (damage < d->damage_threshold)
        event = EVENT_DAMAGE_THRESHOLD;
        damage = 0;
    */

    if (damage_type_resistant(target, flag))
    {
        damage /= 2;
        event.type = EVENT_DAMAGED_RESIST;
    }

    if (damage_type_vulnerable(target, flag))
    {
        damage *= 2;
        event.type = EVENT_DAMAGED_VULNERABLE;
    }

    if (damage_type_immune(target, flag))
    {
        event.type = EVENT_DAMAGED_IMMUNE;
        damage = 0;
    }    

    event.source = source;
    event.target = target;
    event.value = damage;

    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.destructible_components[target].cur_hp <= damage)
    {        
        g.destructible_components[target].cur_hp = 0;
        system_event_emit(&event);
        damage_system_try_kill(target, source);
    }
    else
    {
        g.destructible_components[target].cur_hp -= damage;
        system_event_emit(&event);   
    }
     /* TODO get rid of this debug */
    // text_printf(&g.msg_win, "\nDmg: %d Kind: %d Hp:[%d %d]", damage, flag, g.destructible_components[target].max_hp, g.destructible_components[target].cur_hp);
    
    return 1;
}
 
 /***************************************************
 * private functions
 ***************************************************/

static bool damage_type_immune(entity_id_t actor, damage_flag_t flag)
{
    return (g.destructible_components[actor].immune & flag) != 0;
}

static bool damage_type_resistant(entity_id_t actor, damage_flag_t flag)
{
    return (g.destructible_components[actor].resist & flag) != 0;
}

static bool damage_type_vulnerable(entity_id_t actor, damage_flag_t flag)
{
   return (g.destructible_components[actor].vulnerable & flag) != 0;
}
