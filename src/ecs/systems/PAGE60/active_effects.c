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
#include "ecs/systems/PAGE58/stats_system.h"
#include "ecs/systems/PAGE60/effect_system_priv.h"

#include "ecs/components/components.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

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

/***************************************************
 * private function prototypes
 ***************************************************/

static uint8_t get_free_slot(active_effects_comp_t *effects);
static uint8_t choose_precedence_slot(active_effects_comp_t *effects, const effect_comp_t *new_effect);
static void active_stack_append(active_effects_comp_t *effects, uint8_t slot);
static void active_stack_remove(active_effects_comp_t *effects, uint8_t slot);

/***************************************************
 * public functions
 ***************************************************/
/*
 * @brief Attach an active effect to the target entity
 * @details If the entity's maximum number of active effects has been reached applies precendence rules 
 * @param target The entity to attach the effect to
 * @param source The entity that is applying the effect or INVALID_ENTITY_ID to apply the effect from the system context
 * @param effect The effect to apply
 */
bool_t attach_active_effect(entity_id_t target, entity_id_t source, const effect_t* effect)
{
    event_t event;

    active_effects_comp_t* effects = &active_effect_components[target];

    uint8_t slot = get_free_slot(effects);

    if (slot == INVALID_SLOT)
    {
        util_info("No free slot\n");
        slot = choose_precedence_slot(effects, effect);
        if (slot == INVALID_SLOT)
        {
            util_info("Does not take precendence\n");
            return 0;
        }
    }

    /* Set up new active effect */
    effects->slots[slot].effect.kind = effect->kind;
    effects->slots[slot].effect.duration = effect->duration;
    effects->slots[slot].effect.attribute = effect->attribute;
    effects->slots[slot].effect.magnitude = effect->magnitude;
    effects->slots[slot].source = source;

    active_stack_append(effects, slot);

    event.type = EVENT_ACTIVE_EFFECT_ATTACHED;
    event.target = target;
    event.source = source;
    system_event_emit(&event);

    return 1;
}

void unattach_active_effect(entity_id_t target, uint8_t slot)
{
    event_t event;

    active_effects_comp_t *effects;

    if (!entity_has_component(target, COMPONENT_ACTIVE_EFFECT))
        return;

    effects = &active_effect_components[target];

    active_stack_remove(effects, slot);

    event.type = EVENT_ACTIVE_EFFECT_UNATTACHED;
    /* TODO record source entity? */
    event.source = ENTITY_ID_INVALID;
    event.target = target;
    system_event_emit(&event);    
}

 /*
  * @brief Remove any active effects that were applied by the source entity (e.g. ring of healing) to the target (e.g player)
  * @details Call this function when the source entity is removed (e.g. unequip ring of healing)
  * @param target The entity that was affected by the source entity
  * @param source The source entity of the effect
  */
  void remove_effects_by_source(entity_id_t target, entity_id_t source)
{
    event_t event;

    active_effects_comp_t* effects;
    
    if (!entity_has_component(target, COMPONENT_ACTIVE_EFFECT))
        return;

    effects = &active_effect_components[target];

    uint8_t i = 0;
    while (i < effects->head)
    {
        uint8_t slot = effects->active_stack[i];
        active_effect_comp_t* e = &effects->slots[slot];

        if (e->source == source)
        {
            active_stack_remove(effects, slot);
            /* do NOT increment i — need to re-check swapped entry */

            event.type = EVENT_ACTIVE_EFFECT_UNATTACHED;
            event.target = target;
            event.source = source;
            system_event_emit(&event);    
        }
        else
        {
            i++;
        }
    }
}

int8_t attribute_mod_sum(entity_id_t actor, attribute_t attribute)
{
    int8_t mod_sum = 0;
    
    active_effects_comp_t* effects = &active_effect_components[actor];

    uint8_t i = 0;
    while (i < effects->head)
    {
        int8_t slot = effects->active_stack[i];
        effect_t* e = &effects->slots[slot].effect;

        if ((e->attribute == attribute) && (e->kind == EFFECT_STAT_MODIFIER))
        {
            mod_sum += e->magnitude;
        }
        i++;
    }
    return mod_sum;
}


 
 /***************************************************
 * private functions
 ***************************************************/
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
 * @brief Find a free slot in the entity's effects component
 * @param effects The entity's effects component
 * @return The free slot or INVALID_SLOT
 */
static uint8_t get_free_slot(active_effects_comp_t *effects)
{
    for (uint8_t i = 0; i < MAX_ACTIVE_EFFECTS; i++)
    {
        if (effects->slots[i].effect.kind == EFFECT_NONE)
        {
            return i;
        }
    }

    return INVALID_SLOT;
}

/*
 * @brief Appends the slot to active stack
 * param effects The entity's effects component
 * @param slot The slot to append
 */
static void active_stack_append(active_effects_comp_t *effects, uint8_t slot)
{
    util_assert ( effects->head < MAX_ACTIVE_EFFECTS);

    effects->active_stack[effects->head++] = slot;
}

/*
 * @brief Removes the slot from the active stack via swap-remove 
 * @param effects The entity's effects component
 * @param slot The slot to remove
 */
static void active_stack_remove(active_effects_comp_t *effects, uint8_t slot)
{
    // Clear the slot's effect 
    effects->slots[slot].effect.kind = EFFECT_NONE;

    // Remove slot from active stack
    for (uint8_t i = 0; i < effects->head; i++)
    {
        if (effects->active_stack[i] == slot)
        {
            // Set slot at i to last slot in stack and decrement head
            effects->active_stack[i] = effects->active_stack[--effects->head];
            break;
        }
    }   
}