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

#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/


 /***************************************************
 * private variables (static)
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
/*
 * @brief Apply an effect to the target
 * @param target The entity to apply the effect to
 * @param effect The effect to apply
 */
void apply_effect(entity_id_t target, const effect_t *effect)
{
    /* Resolve the kind of effect */
    switch (effect->kind)
    {
        case EFFECT_DAMAGE:
            system_damage_try_take_damage(target, effect->stat.magnitude, DAMAGE_NONE);
            break;
        case EFFECT_HEAL:
            system_healing_try_take_healing(target, effect->stat.magnitude, HEALING_KIND_HP);
            text_printf(&g.msg_win, "\nYou feel better!"); // TODO remove
            break;
        case EFFECT_STAT_MODIFIER:
        /* Not applicable - stats are not directly modified by effects. */
            break;
        case EFFECT_APPLY_CONDITION:
        {
            if (entity_has_component(target, COMPONENT_CONDITION))
            {
                condition_mask_t mask = CONDITION_MASK(effect->condition);
                if (!(g.condition_components[target].conditions & mask))
                {
                    g.condition_components[target].conditions |= mask;
                    event_t event;
                    event.type   = EVENT_CONDITION_APPLIED;
                    event.source = ENTITY_ID_INVALID;
                    event.target = target;
                    event.value  = (uint8_t)effect->condition;
                    system_event_emit(&event);
                }
            }
            break;
        }
        case EFFECT_REMOVE_CONDITION:
        {
            remove_active_conditions_by_id(target, effect->condition);
            break;
        }
        case EFFECT_TRIGGER_ONLY:
            break;
        default:
            util_abort("Unknown effect type");
    }
}

 /***************************************************
 * private functions
 ***************************************************/