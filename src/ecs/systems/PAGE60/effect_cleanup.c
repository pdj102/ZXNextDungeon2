/**
 * @file effect_system.c
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE60/effect_system.h"
#include "ecs/systems/PAGE60/effect_system_priv.h"

#include "ecs/components/components.h"
#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/active_effect_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/entity.h"

#include "game/game.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/
#define INVALID_SLOT 0xFF

 /***************************************************
 * private variables (static)
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
void cleanup_entity(entity_id_t source)
{
    /* Early out: this entity could not have created active effects */
    if (!entity_has_component(source, COMPONENT_EFFECT))
        return;

    for (entity_id_t e = 0; e < MAX_ENTITIES; ++e)
    {
        if (!entity_has_component(e, COMPONENT_ACTIVE_EFFECT))
            continue;

        active_effects_comp_t *effects = &active_effect_components[e];

        for (uint8_t i = 0; i < effects->head; )
        {
            uint8_t slot = effects->active_stack[i];
            active_effect_comp_t *ae = &effects->slots[slot];

            if (ae->source == source)
            {
                remove_active_effect(effects, slot);
                /* do NOT increment i — stack was compacted */
            }
            else
            {
                ++i;
            }
        }
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/
