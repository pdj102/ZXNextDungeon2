/**
 * @file consumable_system.c
 * @author Paul Johnson
 * @brief consumable system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE62/consumable_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/entity.h"

#include "game/game.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
bool_t consumable_system_try_consume(entity_id_t actor, entity_id_t entity)
{
    event_t event;

    if (!entity_has_component(entity, COMPONENT_CONSUMABLE))
    {
        return 0;
    }

    event.type = EVENT_CONSUMED;
    event.source = actor;
    event.target = entity;
    event.value = 1;

    system_event_emit(event);
    entity_mark_for_destruction(entity);

    return 1;
}
 
 /***************************************************
 * private functions
 ***************************************************/