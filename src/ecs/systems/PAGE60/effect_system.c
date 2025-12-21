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
#define INVALID_SLOT 0xFF

 /***************************************************
 * private variables (static)
 ***************************************************/
__at (0xe000) static active_effect_components_t active_effect_components; /* Place active effects in 8k-slot 7 (MMU7) */

/***************************************************
 * private function prototypes
 ***************************************************/
static void effect_system_apply_effects_by_source( const effect_apply_t *ctx);
static void apply_instant_effect(const effect_apply_t *ctx, const effect_comp_t *effect);
static bool_t apply_active_effect(const effect_apply_t *ctx, const effect_comp_t* effect);
static uint8_t get_free_slot(active_effects_comp_t *effects);
static uint8_t choose_precedence_slot(active_effects_comp_t *effects, const effect_comp_t *new_effect);
void remove_active_effect(active_effects_comp_t* effects, uint8_t slot);
static void active_stack_append(active_effects_comp_t *effects, uint8_t index);
static void active_stack_remove(active_effects_comp_t *effects, uint8_t index);


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
            active_effect_components[i].slots[j].kind = EFFECT_NONE;
        }
    }
}

 void effect_system_handle_event(const event_t event)
{
    effect_apply_t ctx;

    switch (event.type)
    {
        case EVENT_CONSUMED:
            ctx.source = event.target;  /* This is correct - The event Player (source) quaffs Potion (target) becomes Apply Potion's effect (source) to Player (target) */
            ctx.target = event.source;
            ctx.trigger = TRIGGER_ON_CONSUMED;
            effect_system_apply_effects_by_source(&ctx);
            break;
        default:
            util_abort("Unknown event type");
    }
}

static void effect_system_turn_entity(entity_id_t entity)
{
    active_effects_comp_t *effects = &active_effect_components[entity];

    for (uint8_t i = 0; i < effects->head; )
    {
        uint8_t slot = effects->active_stack[i];
        active_effect_comp_t *e = &effects->slots[slot];

        if (e->remaining != 0xFF)
        {
            if (--e->remaining == 0)
            {
                remove_active_effect(effects, slot);
                continue; // don't increment i since we removed an element
            }
        }

        i++;
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/

static void effect_system_apply_effects_by_source( const effect_apply_t *ctx)
{
    effect_comp_t *effect;

    if (!entity_has_component(ctx->source, COMPONENT_EFFECT))
    {
        return;
    }

    /* Get the effect component for the source entity */
    effect = &g.effect_components[ctx->source];

    /* Do nothing if no trigger match */
    if ((effect->triggers & ctx->trigger) == 0)
    {
        return;
    }

    if (effect->duration == 0 )
    {
        apply_instant_effect(ctx, effect);
    }
    else if (entity_has_component(ctx->target, COMPONENT_ACTIVE_EFFECT))
    {
            apply_active_effect(ctx, effect); // ignore result 
    }
}

static void apply_instant_effect(const effect_apply_t *ctx, const effect_comp_t *effect)
{

    switch (effect->kind)
    {
        case EFFECT_INSTANT_DAMAGE:
            system_damage_try_take_damage(ctx->target, effect->magnitude, DAMAGE_NONE);
            break;
        case EFFECT_INSTANT_HEAL:
            system_healing_try_take_healing(ctx->target, effect->magnitude, HEALING_KIND_HP);
            text_printf(&g.msg_win, "You feel better!\n");
            break;
        default:
            util_abort("Unknown effect type");
    }
}

static bool_t apply_active_effect(const effect_apply_t *ctx, const effect_comp_t* effect)
{

    active_effects_comp_t* effects = &active_effect_components[ctx->target];

    uint8_t slot = get_free_slot(effects);

    if (slot == INVALID_SLOT)
    {
        slot = choose_precedence_slot(effects, effect);
        if (slot == INVALID_SLOT)
            return 0;
    }

    /* Set up new active effect */
    effects->slots[slot].kind = effect->kind;
    effects->slots[slot].remaining = effect->duration;
    effects->slots[slot].target = effect->target;
    effects->slots[slot].magnitude = effect->magnitude;

    active_stack_append(effects, slot);
    return 1;
}

/*
 * @brief choose the precedence slot for an effect
 */
static uint8_t choose_precedence_slot(active_effects_comp_t *effects, const effect_comp_t *new_effect)
{
    (void)effects;
    (void)new_effect;
    return INVALID_SLOT;
}


void remove_active_effect(active_effects_comp_t* effects, uint8_t slot)
{
    effects->slots[slot].kind = EFFECT_NONE;
    active_stack_remove(effects, slot);
}




/* 
 * @brief find a free slot
 */
static uint8_t get_free_slot(active_effects_comp_t *effects)
{
    for (uint8_t i = 0; i < MAX_ACTIVE_EFFECTS; i++)
    {
        if (effects->slots[i].kind == EFFECT_NONE)
        {
            return i;
        }
    }

    return INVALID_SLOT;
}

/*
 * @brief appends the slot index to active stack
 */
static void active_stack_append(active_effects_comp_t *effects, uint8_t index)
{
    util_assert ( effects->head < MAX_ACTIVE_EFFECTS);

    effects->active_stack[effects->head++] = index;
}

/*
 * @brief removes the slot index from the active stack
 */
static void active_stack_remove(active_effects_comp_t *effects, uint8_t index)
{
    for (uint8_t i = 0; i < effects->head; i++)
    {
        if (effects->active_stack[i] == index)
        {
            // Set element at i to last element in stack and decrement head
            effects->active_stack[i] = effects->active_stack[--effects->head];
            break;
        }
    }   
}