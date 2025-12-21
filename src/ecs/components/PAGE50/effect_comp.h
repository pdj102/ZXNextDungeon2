/**
 * @file effect_comp.h
 * @author Paul Johnson
 * @brief Describes an effect that could happen 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EFFECT_COMP_H
#define EFFECT_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

#include "game/game.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    EFFECT_NONE = 0,

    /* Instant changes */
    EFFECT_INSTANT_DAMAGE,      /* reduce current HP/MP/etc */
    EFFECT_INSTANT_HEAL,        /* restore current HP/MP/etc */

    /* Persistent stat modifiers */
    EFFECT_STAT_MODIFIER,       /* +/- stat while active */

    /* Status effects */
    EFFECT_APPLY_STATUS,        /* poison, stun, slow, etc */
    EFFECT_REMOVE_STATUS,

    /* Utility / hooks */
    EFFECT_DISPEL,              /* remove other effects */
    EFFECT_TRIGGER_ONLY,        /* no direct change, just emits event */

    EFFECT_COUNT
} effect_kind_t;

typedef enum {
    EFFECT_TARGET_NONE = 0,

    /* Resources */
    EFFECT_TARGET_HP,
    EFFECT_TARGET_MP,

    /* Primary stats */
    EFFECT_TARGET_STR,
    EFFECT_TARGET_DEX,
    EFFECT_TARGET_CON,
    EFFECT_TARGET_INT,
    EFFECT_TARGET_WIS,
    EFFECT_TARGET_CHA,

    /* Secondary stats */
    EFFECT_TARGET_ARMOR_CLASS,
    EFFECT_TARGET_SPEED,
    EFFECT_TARGET_ATTACK,
    EFFECT_TARGET_DAMAGE,

    /* Status slot (used with EFFECT_APPLY_STATUS) */
    EFFECT_TARGET_STATUS,

    EFFECT_TARGET_COUNT
} effect_target_t;

typedef enum {
    TRIGGER_NONE            = 0,
    TRIGGER_ON_CONSUMED     = 1 << 0,       /* eat food, quaff potion*/
    TRIGGER_ON_EQUIPPED     = 1 << 1,       /* wield / wear */
    TRIGGER_ON_UNEQUIPPED   = 1 << 2,        
    TRIGGER_ON_HIT          = 1 << 3,       /* struck by */
    TRIGGER_ON_STEP         = 1 << 4,       /* stepped on */
    TRIGGER_ON_TURN         = 1 << 5,       /* turn occurs*/
} trigger_flag_t;

typedef uint8_t trigger_mask_t; /* bitmask of triggers */

/* A single effect  */
typedef struct {
    effect_kind_t kind;         /* kind of effect */
    int8_t magnitude;           /* magnitude of effect (+ / -) */
    uint8_t duration;           /* duration of effect (turns). 0 = instant effect 0xFF = permanent (until removed) */
    effect_target_t target;     /* effect target */
    trigger_mask_t triggers;    /* when this effect applies */
} effect_comp_t;

typedef effect_comp_t effect_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void effect_add(entity_id_t entity, const effect_comp_t effect);

void effect_remove(entity_id_t entity);

#endif // EFFECT_COMP_H
