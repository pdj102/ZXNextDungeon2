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
static void process_trigger( const trigger_context_t *ctx);
static void apply_instant_effect(const trigger_context_t *ctx, const effect_comp_t *effect);
static bool_t attach_active_effect(const trigger_context_t *ctx, const effect_comp_t* effect);
void apply_active_effect(entity_id_t entity, uint8_t slot);

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
    trigger_context_t ctx;

    switch (event.type)
    {
        case EVENT_CONSUMED:
            ctx.source = event.target;  /* This is correct - The event Player (source) quaffs Potion (target) becomes Apply Potion's effect (source) to Player (target) */
            ctx.target = event.source;
            ctx.trigger = TRIGGER_ON_CONSUMED;
            process_trigger(&ctx);
            break;
        default:
            util_abort("Unknown event type");
    }
}

static void effect_system_process_entity_turn(entity_id_t entity)
{
    active_effects_comp_t *effects = &active_effect_components[entity];

    for (uint8_t i = 0; i < effects->head; )
    {
        uint8_t slot = effects->active_stack[i];
        active_effect_comp_t *e = &effects->slots[slot];

        apply_active_effect(entity, slot);

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

void effect_system_cleanup_entity(entity_id_t source)
{
    /* Early out: this entity could not have created active effects */
    if (!entity_has_component(source, COMPONENT_EFFECT))
        return;

    for (entity_id_t e = 0; e < MAX_ENTITIES; ++e)
    {
        if (!entity_has_component(e, COMPONENT_ACTIVE_EFFECT))
            continue;

        active_effects_comp_t *effects = &active_effect_components[e];

        for (uint8_t i = 0; i < effects->head; )
        {
            uint8_t slot = effects->active_stack[i];
            active_effect_comp_t *ae = &effects->slots[slot];

            if (ae->source == source)
            {
                remove_active_effect(effects, slot);
                /* do NOT increment i — stack was compacted */
            }
            else
            {
                ++i;
            }
        }
    }
}
 
 /***************************************************
 * private functions
 ***************************************************/

 /*
  * @brief Process trigger 
  * @param ctx The context of the effect application. NB the effect applies from the source (e.g. potion) to the target (e.g player)
  */
static void process_trigger( const trigger_context_t *ctx)
{
    effect_comp_t *effect;

    /* Do nothing if the source has no effects */
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
        /* If the effect is instant, apply immediately */
        apply_instant_effect(ctx, effect);
    }
    else if (entity_has_component(ctx->target, COMPONENT_ACTIVE_EFFECT))
    {
        /*  If the effect is durational, attach to the target*/
            attach_active_effect(ctx, effect); // ignore result 
    }
}

/*
 * @brief Apply an instant effect to the target entity
 * @param ctx The context of the effect application 
 * @param effect The effect component to apply
 */
static void apply_instant_effect(const trigger_context_t *ctx, const effect_comp_t *effect)
{

    switch (effect->kind)
    {
        case EFFECT_DAMAGE:
            system_damage_try_take_damage(ctx->target, effect->magnitude, DAMAGE_NONE);
            break;
        case EFFECT_HEAL:
            system_healing_try_take_healing(ctx->target, effect->magnitude, HEALING_KIND_HP);
            text_printf(&g.msg_win, "You feel better!\n");
            break;
        default:
            util_abort("Unknown effect type");
    }
}

/*
 * @brief Apply an entity's active effect 
 */
void apply_active_effect(entity_id_t entity, uint8_t slot)
{
    active_effect_comp_t *e = &active_effect_components[entity].slots[slot];

    switch (e->kind)
    {
        case EFFECT_DAMAGE:
            system_damage_try_take_damage(e->target, e->magnitude, DAMAGE_NONE);
            break;

        case EFFECT_STAT_MODIFIER:
            /* already applied when attached — nothing per turn */
            break;

        default:
            break;
    }
}

 /*
  * @brief Remove any active effects that were applied by the source entity (e.g. ring of healing) to the target (e.g player)
  * @details Call this function when the source entity is removed (e.g. unequip ring of healing)
  * @param ctx The context of the effect application. 
  */
void remove_effects_by_source(const trigger_context_t *ctx)
{
    active_effects_comp_t* effects = &active_effect_components[ctx->target];

    uint8_t i = 0;
    while (i < effects->head)
    {
        uint8_t slot = effects->active_stack[i];
        active_effect_comp_t* e = &effects->slots[slot];

        if (e->source == ctx->source)
        {
            /* clear slot */
            e->kind = EFFECT_NONE;

            /* remove from active stack via swap-remove */
            effects->active_stack[i] = effects->active_stack[--effects->head];

            /* do NOT increment i — need to re-check swapped entry */
        }
        else
        {
            i++;
        }
    }
}

/*
 * @brief Attach an active effect to the target entity
 * @details If the entity's maximum number of active effects has been reached applies precendence rules 
 * @param ctx The context of the effect application 
 * @param effect The effect component to apply
 */
static bool_t attach_active_effect(const trigger_context_t *ctx, const effect_comp_t* effect)
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
    effects->slots[slot].source = ctx->source;

    active_stack_append(effects, slot);

    util_info("Attached active effect\n");
    return 1;
}

/*
 * @brief choose the precedence slot for an effect
 * @param effects The effect component to check
 * @param new_effect The effect to check against
 */
static uint8_t choose_precedence_slot(active_effects_comp_t *effects, const effect_comp_t *new_effect)
{
    (void)effects;
    (void)new_effect;
    return INVALID_SLOT;
}

/*
 * @brief Remove an active effect from an entity
 * @param effects The entity's effects component
 * @param slot The slot to remove the effect from
 */
void remove_active_effect(active_effects_comp_t* effects, uint8_t slot)
{
    effects->slots[slot].kind = EFFECT_NONE;
    active_stack_remove(effects, slot);
}

/* 
 * @brief Find a free slot in the entity's effects component
 * @param effects The entity's effects component
 * @return The free slot or INVALID_SLOT
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
 * @brief Appends the slot index to active stack
 * param effects The entity's effects component
 * @param index The slot to append
 */
static void active_stack_append(active_effects_comp_t *effects, uint8_t index)
{
    util_assert ( effects->head < MAX_ACTIVE_EFFECTS);

    effects->active_stack[effects->head++] = index;
}

/*
 * @brief Removes the slot index from the active stack via swap-remove 
 * @param effects The entity's effects component
 * @param index The slot to remove
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