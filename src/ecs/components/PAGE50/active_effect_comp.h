/**
 * @file active_effect_comp.h
 * @author Paul Johnson
 * @brief Describes an active effect 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ACTIVE_EFFECT_COMP_H
#define ACTIVE_EFFECT_COMP_H

#include <stdint.h>

#include "ecs/components/PAGE50/effect_comp.h"

#include "core/util.h"

#include "ecs/entity.h"

#include "game/game.h"

/***************************************************
 * public defines
 ***************************************************/
#define MAX_ACTIVE_EFFECTS 4

/***************************************************
 * public types
 ***************************************************/

/* An active effect */
typedef struct {
    effect_kind_t kind;         /* kind of effect */
    int8_t magnitude;           /* magnitude of effect (+ / -) */
    uint8_t remaining;          /* remaining number of turns. 0xFF = permanent (until removed) */
    effect_target_t target;     /* effect target */
} active_effect_comp_t;

/* Each entity can have up to MAX_ACTIVE_EFFECTS active effects */
typedef struct {
    active_effect_comp_t slots[MAX_ACTIVE_EFFECTS]; /* slots for effects */

    uint8_t active_stack[MAX_ACTIVE_EFFECTS];   /* stack of active slots */
    uint8_t head;                               /* head of stack */
} active_effects_comp_t;

typedef active_effects_comp_t active_effect_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void active_effect_add(entity_id_t entity);

void active_effect_remove(entity_id_t entity);

#endif // ACTIVE_EFFECT_COMP_H
