/**
 * @file healing_system.c
 * @author Paul Johnson
 * @brief healing system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE66/healing_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private function prototypes
 ***************************************************/
static bool_t healing_type_immune(entity_id_t actor, healing_type_t type);
static bool_t healing_type_resistant(entity_id_t actor, healing_type_t type);
static bool_t healing_type_vulnerable(entity_id_t actor, healing_type_t type);

/***************************************************
 * public functions
 ***************************************************/
bool_t healing_system_try_die(entity_id_t entity)
{
    event_t event;

    if (!entity_has_component(entity, COMPONENT_DESTRUCTIBLE))
    {
        return 0;
    }
    
    event.type = EVENT_DIED;
    event.source = entity;
    event.target = ENTITY_ID_INVALID;
    event.value = 0;
    system_event_emit(event);

    /* TODO: This should not be done here. Destroyed creatures, items etc should respond to event*/
    g.creature_components[entity].status = CREATURE_STATUS_DEAD;
    entity_mark_for_destruction(entity);

    return 1;
}

int8_t healing_system_try_take_healing(entity_id_t actor, int8_t healing, healing_type_t type)
{
    event_t event;

    event.type = EVENT_HEALINGD;

    if (!entity_has_component(actor, COMPONENT_DESTRUCTIBLE ))
    {
        return 0;
    }

    /* TODO: Implement checking healing is above threshold*/
    /* if (healing < d->healing_threshold)
        event = EVENT_HEALING_THRESHOLD;
        healing = 0;
    */

    if (healing_type_resistant(actor, type))
    {
        healing /= 2;
        event.type = EVENT_HEALINGD_RESIST;
    }

    if (healing_type_vulnerable(actor, type))
    {
        healing *= 2;
        event.type = EVENT_HEALINGD_VULNERABLE;
    }

    if (healing_type_immune(actor, type))
    {
        event.type = EVENT_HEALINGD_IMMUNE;
        healing = 0;
    }    

    event.source = actor;
    event.target = ENTITY_ID_INVALID;
    event.value = healing;

    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by healing */
    if (g.destructible_components[actor].cur_hp <= healing)
    {        
        g.destructible_components[actor].cur_hp = 0;
        system_event_emit(event);
        healing_system_try_die(actor);
    }
    else
    {
        g.destructible_components[actor].cur_hp -= healing;
        system_event_emit(event);

        text_printf(&g.msg_win, "Dmg: %d Hp:[%d %d]", healing, g.destructible_components[actor].max_hp, g.destructible_components[actor].cur_hp);
    }
    
    return 1;
}
 
 /***************************************************
 * private functions
 ***************************************************/

static bool_t healing_type_immune(entity_id_t actor, healing_type_t type)
{
    return (g.destructible_components[actor].immune & type) != 0;
}

static bool_t healing_type_resistant(entity_id_t actor, healing_type_t type)
{
   return (g.destructible_components[actor].resist & type) != 0;
}

static bool_t healing_type_vulnerable(entity_id_t actor, healing_type_t type)
{
   // return 0;
   return (g.destructible_components[actor].vulnerable & type) != 0;
}
