/**
 * @file perception_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "perception_system.h"

#include "ecs/entity.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "game/global_state.h"

#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/

 /***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
bool perception_system_try_check(entity_id_t creature)
{
    event_t event;

    if (g.player.id == ENTITY_ID_INVALID)
        return 0;

    if (map_has_line_of_sight(g.player.id, creature))
    {
        event.type = EVENT_SPOTTED_TARGET;
        event.source = creature;
        event.target = g.player.id;
        system_event_emit(&event);
        return 1;
    }

    return 0; 
}

bool perception_system_can_see_target(entity_id_t ai, entity_id_t target)
{
    return map_has_line_of_sight(ai, target);
}