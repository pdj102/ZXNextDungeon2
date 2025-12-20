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
            ctx.trigger = TRIGGER_CONSUMED;
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

    if (g.effect_components[ctx.source].duration == 0 && (g.effect_components[ctx.source].trigger & ctx.trigger))
    {
        apply_instant_effect(ctx);
    }
}


static void apply_instant_effect(const effect_apply_t ctx)
{
    switch (g.effect_components[ctx.source].type)
    {
        case EFFECT_DAMAGE_HP:
            system_damage_try_take_damage(ctx.target, g.effect_components[ctx.source].value, DAMAGE_KIND_NONE);
            break;
        case EFFECT_RESTORE_HP:
            text_printf(&g.msg_win, "You feel better!\n");
            break;
        default:
            util_abort("Unknown effect type");
    }
}