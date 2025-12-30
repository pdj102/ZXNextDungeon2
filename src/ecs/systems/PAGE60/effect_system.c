/**
 * @file effect_system.c
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE58/stats_system.h"
#include "ecs/systems/PAGE60/effect_system.h"
#include "ecs/systems/PAGE60/effect_system_priv.h"

#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"

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
void effect_system_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        active_effect_components[i].head = 0;
        for (uint8_t j = 0; j < MAX_ACTIVE_EFFECTS; j++)
        {
            active_effect_components[i].slots[j].effect.kind = EFFECT_NONE;
        }
    }
}



void effect_system_handle_event(const event_t *event)
{
    handle_event(event);
}

void effect_system_process_entity_turn(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_ACTIVE_EFFECT));

    entity_turn(entity);
}

int8_t effect_system_attribute_mod_sum(entity_id_t actor, attribute_t attribute)
{
    util_assert(actor < MAX_ENTITIES);
    util_assert(entity_has_component(actor, COMPONENT_ACTIVE_EFFECT));

    return attribute_mod_sum(actor, attribute);
}

void effect_system_cleanup_entity(entity_id_t source)
{
    cleanup_entity(source);
}

 /***************************************************
 * private functions
 ***************************************************/