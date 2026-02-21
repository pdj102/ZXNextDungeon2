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

static uint8_t get_free_slot(entity_id_t entity);
static uint8_t choose_precedence_slot(entity_id_t entity, const effect_comp_t *new_effect);
static void active_stack_append(entity_id_t entity, uint8_t slot);
static void active_stack_remove(entity_id_t entity, uint8_t slot);

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
bool attach_active_effect(entity_id_t target, entity_id_t source, const effect_t* effect)
{
    event_t event;

    uint8_t slot = get_free_slot(target);

    if (slot == INVALID_SLOT)
    {
        util_info("No free slot");
        slot = choose_precedence_slot(target, effect);
        if (slot == INVALID_SLOT)
        {
            util_info("Does not take precendence");
            return 0;
        }
    }

    /* Set up new active effect */
    g.active_effect_components->slots[target][slot].effect.kind = effect->kind;
    g.active_effect_components->slots[target][slot].effect.duration = effect->duration;
    g.active_effect_components->slots[target][slot].effect.attribute = effect->attribute;
    g.active_effect_components->slots[target][slot].effect.magnitude = effect->magnitude;
    g.active_effect_components->slots[target][slot].source = source;

    active_stack_append(target, slot);

    event.type = EVENT_ACTIVE_EFFECT_ATTACHED;
    event.target = target;
    event.source = source;
    system_event_emit(&event);

    return 1;
}

void unattach_active_effect(entity_id_t target, uint8_t slot)
{
    event_t event;

    if (!entity_has_component(target, COMPONENT_ACTIVE_EFFECT))
        return;

    active_stack_remove(target, slot);

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

    if (!entity_has_component(target, COMPONENT_ACTIVE_EFFECT))
        return;

    uint8_t i = 0;
    while (i < g.active_effect_components->head[target])
    {
        uint8_t slot = g.active_effect_components->active_stack[target][i];
        active_effect_comp_t* e = &g.active_effect_components->slots[target][slot];

        if (e->source == source)
        {
            active_stack_remove(target, slot);
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

    uint8_t i = 0;
    while (i < g.active_effect_components->head[actor])
    {
        int8_t slot = g.active_effect_components->active_stack[actor][i];
        effect_t* e = &g.active_effect_components->slots[actor][slot].effect;

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
 * @param entity The entity to check
 * @param new_effect The effect to check against
 */
static uint8_t choose_precedence_slot(entity_id_t entity, const effect_comp_t *new_effect)
{
    (void)entity;
    (void)new_effect;
    return INVALID_SLOT;
}

/*
 * @brief Find a free slot in the entity's effects component
 * @param entity The entity to check
 * @return The free slot or INVALID_SLOT
 */
static uint8_t get_free_slot(entity_id_t entity)
{
    for (uint8_t i = 0; i < MAX_ACTIVE_EFFECTS; i++)
    {
        if (g.active_effect_components->slots[entity][i].effect.kind == EFFECT_NONE)
        {
            return i;
        }
    }

    return INVALID_SLOT;
}

/*
 * @brief Appends the slot to active stack
 * @param entity The entity
 * @param slot The slot to append
 */
static void active_stack_append(entity_id_t entity, uint8_t slot)
{
    util_assert(g.active_effect_components->head[entity] < MAX_ACTIVE_EFFECTS);

    g.active_effect_components->active_stack[entity][g.active_effect_components->head[entity]++] = slot;
}

/*
 * @brief Removes the slot from the active stack via swap-remove
 * @param entity The entity
 * @param slot The slot to remove
 */
static void active_stack_remove(entity_id_t entity, uint8_t slot)
{
    // Clear the slot's effect
    g.active_effect_components->slots[entity][slot].effect.kind = EFFECT_NONE;
    g.active_effect_components->slots[entity][slot].source = ENTITY_ID_INVALID;

    // Remove slot from active stack
    for (uint8_t i = 0; i < g.active_effect_components->head[entity]; i++)
    {
        if (g.active_effect_components->active_stack[entity][i] == slot)
        {
            // Set slot at i to last slot in stack and decrement head
            g.active_effect_components->active_stack[entity][i] = g.active_effect_components->active_stack[entity][--g.active_effect_components->head[entity]];
            break;
        }
    }
}
