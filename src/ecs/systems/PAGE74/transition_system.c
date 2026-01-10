/**
 * @file transition_system.c
 * @author Paul Johnson
 * @brief Transition system
 */

#include "transition_system.h"

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

bool transition_system_try(entity_id_t source, entity_id_t target)
{
    event_t event;

    if (!entity_has_component(source, COMPONENT_TRANSITION))
        return false;

    event.type = EVENT_TRANSITION;
    event.source = source;
    event.target = target;
    event.value = g.transition_components[source].delta_depth;

    system_event_emit(&event);

    return true;
}

/***************************************************
 * private functions
 ****************************************************/
