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
#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/entity.h"

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

    /* If entity has active effects clean up*/
    if (entity_has_component(source, COMPONENT_ACTIVE_EFFECT))
    {
        g.active_effect_components[source]->head = 0;
        for (uint8_t j = 0; j < MAX_ACTIVE_EFFECTS; j++)
        {
            g.active_effect_components[source]->slots[j].effect.kind = EFFECT_NONE;
        }
    }

    /* Early out: this entity could not bestow active effects */
    if (!entity_has_component(source, COMPONENT_EFFECT))
        return;

    entity_id_t entity;         

    /* Iterate through all active entities, and remove all effects bestowed by source */
    for (uint8_t i = 0; i < g.entity_components.active_head; i++)
    {
        entity = g.entity_components.active_list[i];

        if (!entity_has_component(entity, COMPONENT_ACTIVE_EFFECT))
            continue;

        /* Remove any active effects bestowed by source */
        remove_effects_by_source(entity, source);
    }
}

/***************************************************
 * private functions
 ***************************************************/
