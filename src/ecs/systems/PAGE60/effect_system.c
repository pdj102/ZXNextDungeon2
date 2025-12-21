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
#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/active_effect_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/entity.h"

#include "game/game.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

 /***************************************************
 * private variables (static)
 ***************************************************/
__at (0xe000) static active_effect_components_t active_effect_components; /* Place active effects in 8k-slot 7 (MMU7) */

/***************************************************
 * private function prototypes
 ***************************************************/
static void effect_system_apply_effects_by_source( const effect_apply_t ctx);
static void apply_instant_effect(const effect_apply_t ctx);

/***************************************************
 * public functions
 ***************************************************/
void effect_system_handle_event(const event_t event)
{
    effect_apply_t ctx;

    switch (event.type)
    {
        case EVENT_CONSUMED:
            ctx.source = event.target;  /* This is correct - The event Player (source) quaffs Potion (target) becomes Apply Potion's effect (source) to Player (target) */
            ctx.target = event.source;
            ctx.trigger = TRIGGER_ON_CONSUMED;
            effect_system_apply_effects_by_source(ctx);
            break;
        default:
            util_abort("Unknown event type");
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/

static void effect_system_apply_effects_by_source( const effect_apply_t ctx)
{
    if (!entity_has_component(ctx.source, COMPONENT_EFFECT))
    {
        return;
    }

    if (g.effect_components[ctx.source].duration == 0 && (g.effect_components[ctx.source].triggers & ctx.trigger))
    {
        apply_instant_effect(ctx);
    }
}


static void apply_instant_effect(const effect_apply_t ctx)
{
    switch (g.effect_components[ctx.source].kind)
    {
        case EFFECT_INSTANT_DAMAGE:
            system_damage_try_take_damage(ctx.target, g.effect_components[ctx.source].value, DAMAGE_NONE);
            break;
        case EFFECT_INSTANT_HEAL:
            system_healing_try_take_healing(ctx.target, g.effect_components[ctx.source].value, HEALING_KIND_HP);
            text_printf(&g.msg_win, "You feel better!\n");
            break;
        default:
            util_abort("Unknown effect type");
    }
}