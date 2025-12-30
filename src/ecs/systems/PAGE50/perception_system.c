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

#include "game/game.h"
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
uint8_t perception_system_try_check(entity_id_t creature)
{
    uint8_t result; 
    event_t event;

    result = map_has_line_of_sight(g.player.id, creature);

    if (result == 1)
    {
        util_info("Seen\n");

        event.type = EVENT_SPOTTED_TARGET;
        event.source = creature;
        event.target = g.player.id;
        system_event_emit(&event);
    }

    return result; 
}