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
void entity_turn(entity_id_t entity)
{
    event_t event;

    active_effects_comp_t *effects = &active_effect_components[entity];

    for (uint8_t i = 0; i < effects->head; )
    {
        uint8_t slot = effects->active_stack[i];
        effect_t *e = &effects->slots[slot].effect;

        apply_effect(entity, e);

        if (e->duration != 0xFF)
        {
            if (--e->duration == 0)
            {
                unattach_active_effect(entity, slot);
                event.type = EVENT_ACTIVE_EFFECT_EXPIRED;
                event.target = entity;
                system_event_emit(event);    
                continue; // don't increment i since we removed an element
            }
        }

        i++;
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/

 