/**
 * @file effect_system.c
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE60/effect_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/entity.h"

#include "game/game.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void apply_instant_effect(entity_id_t target, entity_id_t source );

/***************************************************
 * public functions
 ***************************************************/
void effect_system_apply_effects_by_source(entity_id_t target, entity_id_t source, effect_trigger_t trigger)
{

    if (!entity_has_component(source, COMPONENT_EFFECT))
    {
        return;
    }

    if (g.effect_components[source].duration == 0 && (g.effect_components[source].trigger & trigger))
    {
        apply_instant_effect(target, source);
    }
}

 
 /***************************************************
 * private functions
 ***************************************************/

static void apply_instant_effect(entity_id_t target, entity_id_t source )
{
    switch (g.effect_components[source].type)
    {
        case EFFECT_DAMAGE_HP:
            system_damage_try_take_damage(target, g.effect_components[source].value, DAMAGE_NONE);
            break;
        case EFFECT_RESTORE_HP:
            break;
        default:
            util_abort("Unknown effect type");
    }

}