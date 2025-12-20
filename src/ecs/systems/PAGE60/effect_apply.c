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

#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/active_effect_comp.h"

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
        case EFFECT_ATTRIBUTE_CUR_HP:
            system_damage_try_take_damage(target, effect->magnitude, DAMAGE_NONE);
            break;
        case EFFECT_ATTRIBUTE_CUR_MP:
        case EFFECT_ATTRIBUTE_MAX_HP:
        case EFFECT_ATTRIBUTE_MAX_MP:

        /* Primary stats */
        case EFFECT_ATTRIBUTE_STR:
        case EFFECT_ATTRIBUTE_DEX:
        case EFFECT_ATTRIBUTE_CON:
        case EFFECT_ATTRIBUTE_INT:
        case EFFECT_ATTRIBUTE_WIS:
        case EFFECT_ATTRIBUTE_CHA:

        /* Secondary stats */
        case EFFECT_ATTRIBUTE_ARMOR_CLASS:
        case EFFECT_ATTRIBUTE_SPEED:
        case EFFECT_ATTRIBUTE_ATTACK:
        case EFFECT_ATTRIBUTE_DAMAGE:
            break;

        /* Status slot (used with EFFECT_APPLY_STATUS) */
        EFFECT_ATTRIBUTE_STATUS:
    }
}

static void apply_healing_effect(entity_id_t target, const effect_comp_t *effect)
{
    switch (effect->attribute)
    {
        case EFFECT_ATTRIBUTE_CUR_HP:
            system_healing_try_take_healing(target, effect->magnitude, HEALING_KIND_HP);
            break;
        case EFFECT_ATTRIBUTE_CUR_MP:
        case EFFECT_ATTRIBUTE_MAX_HP:
        case EFFECT_ATTRIBUTE_MAX_MP:

        /* Primary stats */
        case EFFECT_ATTRIBUTE_STR:
        case EFFECT_ATTRIBUTE_DEX:
        case EFFECT_ATTRIBUTE_CON:
        case EFFECT_ATTRIBUTE_INT:
        case EFFECT_ATTRIBUTE_WIS:
        case EFFECT_ATTRIBUTE_CHA:

        /* Secondary stats */
        case EFFECT_ATTRIBUTE_ARMOR_CLASS:
        case EFFECT_ATTRIBUTE_SPEED:
        case EFFECT_ATTRIBUTE_ATTACK:
        case EFFECT_ATTRIBUTE_DAMAGE:
            break;

        /* Status slot (used with EFFECT_APPLY_STATUS) */
        EFFECT_ATTRIBUTE_STATUS:
    }
}