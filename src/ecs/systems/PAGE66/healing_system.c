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

/***************************************************
 * public functions
 ***************************************************/

int8_t healing_system_try(entity_id_t actor, int8_t amount, healing_kind_t kind)
{
    event_t event;

    if (!entity_has_component(actor, COMPONENT_DESTRUCTIBLE))
    {
        return 0;
    }

    event.source = actor;
    event.target = ENTITY_ID_INVALID;

    if (kind == HEALING_KIND_HP)
    {
        event.type = EVENT_HEALED_HP;

        /* clamp amount to max hp */
        if (g.destructible_components[actor].cur_hp + amount > g.destructible_components[actor].max_hp)
        {
            amount = g.destructible_components[actor].max_hp - g.destructible_components[actor].cur_hp; 
        }

        g.destructible_components[actor].cur_hp += amount;
        event.value = (uint8_t)amount;
        system_event_emit(event);
        
    }
    
    return 1;
}
 
 /***************************************************
 * private functions
 ***************************************************/

static bool_t healing_type_immune(entity_id_t actor, healing_kind_t type)
{
    return (g.destructible_components[actor].immune & type) != 0;
}

static bool_t healing_type_resistant(entity_id_t actor, healing_kind_t type)
{
   return (g.destructible_components[actor].resist & type) != 0;
}

static bool_t healing_type_vulnerable(entity_id_t actor, healing_kind_t type)
{
   // return 0;
   return (g.destructible_components[actor].vulnerable & type) != 0;
}
