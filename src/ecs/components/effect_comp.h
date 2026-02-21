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
#include "ecs/components/condition_comp.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    ATTRIBUTE_NONE = 0,

    /* Resources */
    ATTRIBUTE_CUR_HP,
    ATTRIBUTE_CUR_MP,
    ATTRIBUTE_MAX_HP,
    ATTRIBUTE_MAX_MP,    

    /* Primary stats */
    ATTRIBUTE_STR,
    ATTRIBUTE_DEX,
    ATTRIBUTE_CON,
    ATTRIBUTE_INT,
    ATTRIBUTE_WIS,
    ATTRIBUTE_CHA,

    /* Secondary stats */
    ATTRIBUTE_ARMOR_CLASS,
    ATTRIBUTE_SPEED,
    ATTRIBUTE_ATTACK,
    ATTRIBUTE_DAMAGE,

    ATTRIBUTE_COUNT
} attribute_t;

typedef enum {
    EFFECT_NONE = 0,

    /* Direct stat changes */
    EFFECT_DAMAGE,              /* reduce a resource or decrease a stat by a fixed amount once or per turn if active effect e.g. current hp*/
    EFFECT_HEAL,                /* restore a resource or decrease a stat by a fixed amount once or per turn if active effect e.g. current hp */

    /* Persistent stat modifiers */
    EFFECT_STAT_MODIFIER,       /* apply +/- modifier to a resource or stat while active e.g. +1 */

    /* Condition effects */
    EFFECT_APPLY_CONDITION,        /* apply a condition e.g. poisoned, blinded, incapacitated etc */
    EFFECT_REMOVE_CONDITION,       /* remove a condition e.g. remove blindness etc */

    /* Utility / hooks */
    EFFECT_TRIGGER_ONLY,        /* no direct change, just emits event */

    EFFECT_COUNT
} effect_kind_t;

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
    effect_kind_t  kind;        /* kind of effect */
    uint8_t        duration;    /* Instant effect = 0. Duration effect = number of turns or 0xFF if permanent (until removed) */
    trigger_mask_t triggers;    /* The triggers that cause the effect to trigger */
    union {
        struct {
            int8_t      magnitude;  /* DAMAGE, HEAL, STAT_MODIFIER: signed quantity (+ / -) */
            attribute_t attribute;  /* DAMAGE, HEAL, STAT_MODIFIER: stat / resource the effect applies to e.g. HP */
        } stat;                     /* named — required for SDCC designated-initializer support */
        condition_id_t condition;   /* APPLY_CONDITION, REMOVE_CONDITION: which condition */
    };
} effect_t;

typedef effect_t effect_comp_t; /* Effect component is an effect */

typedef effect_t effect_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // EFFECT_COMP_H
