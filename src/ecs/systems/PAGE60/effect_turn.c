/**
 * @file effect_system.c
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE60/effect_system.h"
#include "ecs/systems/PAGE60/effect_system_priv.h"

#include "ecs/entity.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "core/text.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

 /***************************************************
 * private variables (static)
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
/*
 * @brief Called when an entity takes a turn. Applies all active effects on the entity, reduces their duration, and removes any that have expired.
 */
 void entity_turn(entity_id_t entity)
{
    event_t event;

    /* Loop through active effects on the entity and apply them. If any duration-based effects expire, remove them and emit an event. */
    for (uint8_t i = 0; i < g.active_effect_components->head[entity]; )
    {
        uint8_t slot = g.active_effect_components->active_stack[entity][i];
        effect_t *e = &g.active_effect_components->slots[entity][slot].effect;
        entity_id_t source = g.active_effect_components->slots[entity][slot].source;

        apply_effect(entity, source, e);

        if (e->duration != 0xFF)
        {
            if (--e->duration == 0)
            {
                unattach_active_effect(entity, slot);
                event.type = EVENT_ACTIVE_EFFECT_EXPIRED;
                event.source = source;
                event.target = entity;
                system_event_emit(&event);
                continue; // don't increment i since we removed an element
            }
        }

        i++;
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/

 