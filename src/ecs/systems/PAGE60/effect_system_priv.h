/**
 * @file effect_system.h
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EFFECT_SYSTEM_PRIV_H
#define EFFECT_SYSTEM_PRIV_H

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/condition_comp.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"


/***************************************************
 * Defines
 ***************************************************/

#define INVALID_SLOT 0xFF

/***************************************************
 * Types
 ***************************************************/
typedef struct
{
    entity_id_t     source;   /* Source entity (e.g. item, weapon, trap, aura, etc.) */
    entity_id_t     target;   /* Target entity (e.g. player, monster etc.) */
    trigger_flag_t  trigger;  /* Trigger */
} trigger_context_t;

 /***************************************************
 * private variables (static)
 ***************************************************/
// __at (0xe000) static active_effect_components_t active_effect_components; /* Place active effects in 8k-slot 7 (MMU7) */

/***************************************************
 * Function prototypes
 ***************************************************/


/* Active effects */
bool attach_active_effect(entity_id_t target, entity_id_t source, const effect_t* effect);
void unattach_active_effect(entity_id_t target, uint8_t slot);
void remove_effects_by_source(entity_id_t target, entity_id_t source);
void remove_active_conditions_by_id(entity_id_t target, condition_id_t condition_id);
void condition_clear_if_no_remaining(entity_id_t target, condition_id_t condition_id);
int8_t attribute_mod_sum(entity_id_t actor, attribute_t attribute);

/* Apply effects */
void apply_effect(entity_id_t target, const effect_t *effect);

/* Cleanup */
void cleanup_entity(entity_id_t source);

/* Trigger */
void handle_event(const event_t *event);

/* Turn */
void entity_turn(entity_id_t entity);

#endif // EFFECT_SYSTEM_PRIV_H
