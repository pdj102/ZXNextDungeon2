/**
 * @file door_system.c
 * @author Paul Johnson
 * @brief Door system
 */

#include "door_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ****************************************************/

/***************************************************
 * public functions
 ***************************************************/

bool door_system_try_open(entity_id_t actor, entity_id_t entity)
{
    event_t event;

    if (!entity_has_component(entity, COMPONENT_OPENABLE))
        return false;

    // If open return
    if (g.openable_components[entity].is_open)
        return false;

    // TODO If locked 

    g.openable_components[entity].is_open = true;
    g.renderable_components[entity].tile.tile_id = '\'';
    entity_clear_flag(entity, FLAG_BLOCKING);
    entity_clear_flag(entity, FLAG_BLOCK_LOS);

    event.source = actor;
    event.target = entity;
    event.type = EVENT_OPENED;

    system_event_emit(&event);

    return true;
}

bool door_system_try_close(entity_id_t actor, entity_id_t entity)
{
    event_t event;

    if (!entity_has_component(entity, COMPONENT_OPENABLE))
        return false;

    // If closed return
    if (!g.openable_components[entity].is_open)
        return false;

    g.openable_components[entity].is_open = false;
    g.renderable_components[entity].tile.tile_id = '+';
    entity_set_flag(entity, FLAG_BLOCKING);
    entity_set_flag(entity, FLAG_BLOCK_LOS);    

    event.source = actor;
    event.target = entity;
    event.type = EVENT_CLOSED;

    system_event_emit(&event);

    return true;
}

/***************************************************
 * private functions
 ****************************************************/

 