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
 * private function prototypes
 ***************************************************/
static void apply_damage_effect(entity_id_t target, const effect_comp_t *effect);
static void apply_healing_effect(entity_id_t target, const effect_comp_t *effect);

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
            system_damage_try_take_damage(target, effect->magnitude, DAMAGE_NONE);
            break;
        case EFFECT_HEAL:
            system_healing_try_take_healing(target, effect->magnitude, HEALING_KIND_HP);
            text_printf(&g.msg_win, "You feel better!\n"); // TODO remove
            break;
        case EFFECT_STAT_MODIFIER:
        /* Not applicable - stats are not directly modified by effects. */
            break;
        case EFFECT_APPLY_STATUS:
        case EFFECT_REMOVE_STATUS:
        case EFFECT_TRIGGER_ONLY:
            break;
        default:
            util_abort("Unknown effect type");
    }
}

 /***************************************************
 * private functions
 ***************************************************/


static void apply_damage_effect(entity_id_t target, const effect_comp_t *effect)
{
    switch (effect->attribute)
    {
        case ATTRIBUTE_CUR_HP:
            system_damage_try_take_damage(target, effect->magnitude, DAMAGE_NONE);
            break;
        case ATTRIBUTE_CUR_MP:
        case ATTRIBUTE_MAX_HP:
        case ATTRIBUTE_MAX_MP:

        /* Primary stats */
        case ATTRIBUTE_STR:
        case ATTRIBUTE_DEX:
        case ATTRIBUTE_CON:
        case ATTRIBUTE_INT:
        case ATTRIBUTE_WIS:
        case ATTRIBUTE_CHA:

        /* Secondary stats */
        case ATTRIBUTE_ARMOR_CLASS:
        case ATTRIBUTE_SPEED:
        case ATTRIBUTE_ATTACK:
        case ATTRIBUTE_DAMAGE:
            break;

        /* Status slot (used with EFFECT_APPLY_STATUS) */
        ATTRIBUTE_STATUS:
    }
}

static void apply_healing_effect(entity_id_t target, const effect_comp_t *effect)
{
    switch (effect->attribute)
    {
        case ATTRIBUTE_CUR_HP:
            system_healing_try_take_healing(target, effect->magnitude, HEALING_KIND_HP);
            break;
        case ATTRIBUTE_CUR_MP:
        case ATTRIBUTE_MAX_HP:
        case ATTRIBUTE_MAX_MP:

        /* Primary stats */
        case ATTRIBUTE_STR:
        case ATTRIBUTE_DEX:
        case ATTRIBUTE_CON:
        case ATTRIBUTE_INT:
        case ATTRIBUTE_WIS:
        case ATTRIBUTE_CHA:

        /* Secondary stats */
        case ATTRIBUTE_ARMOR_CLASS:
        case ATTRIBUTE_SPEED:
        case ATTRIBUTE_ATTACK:
        case ATTRIBUTE_DAMAGE:
            break;

        /* Status slot (used with EFFECT_APPLY_STATUS) */
        ATTRIBUTE_STATUS:
    }
}