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

#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/components/PAGE50/active_effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"

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
static void process_trigger( const trigger_context_t *ctx);


/***************************************************
 * public functions
 ***************************************************/

 /*
  * @brief Derive an effect trigger from a game event/
  * @details 
  * Translates a game event (e.g. EVENT_CONSUMED, EVENT_HIT) into an
  * effect trigger and populates a trigger context with source, target,
  * and trigger type for use by the effect system.
  */
void handle_event(const event_t *event)
{
    trigger_context_t ctx;

    ctx.source = event->target;  /* This is correct - The event Player (source) quaffs Potion (target) becomes Apply Potion's effect (source) to Player (target) */
    ctx.target = event->source;

    switch (event->type)
    {
        case EVENT_CONSUMED:
            ctx.trigger = TRIGGER_ON_CONSUMED;
            break;
        case EVENT_EQUIPPED:
            ctx.trigger = TRIGGER_ON_EQUIPPED;
            break;
        default:
            return;
    }

    process_trigger(&ctx);
}

 /***************************************************
 * private functions
 ***************************************************/

 /*
  * @brief Process trigger and apply triggered effects, including instant effects and attaching active effects to target entity 
  * @param ctx The context of the effect application. The effect applies from the source (e.g. potion) to the target (e.g player)
  */
static void process_trigger( const trigger_context_t *ctx)
{
    effect_comp_t *effect;

    /* Do nothing if the source has no effect to apply */
    if (!entity_has_component(ctx->source, COMPONENT_EFFECT))
    {
        return;
    }

    /* Get source entity's effect */
    effect = &g.effect_components[ctx->source];

    /* Do nothing if trigger is not a trigger for the effect */
    if ((effect->triggers & ctx->trigger) == 0)
    {
        return;
    }
    
    if (effect->duration == 0 )
    {
        /* If the effect is instant, apply immediately */
        apply_effect(ctx->target, effect);
    }
    else if (entity_has_component(ctx->target, COMPONENT_ACTIVE_EFFECT))
    {
        /*  If the effect is durational, attach to the target*/
        attach_active_effect(ctx->target, ctx->source, effect); // ignore result 
    }
}