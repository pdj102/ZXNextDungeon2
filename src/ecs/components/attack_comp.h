/**
 * @file melee_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ATTACK_COMP_H
#define ATTACK_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/dice.h"

#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    ATTACK_KIND_NONE,
    ATTACK_KIND_MELEE,
    ATTACK_KIND_RANGED,
    ATTACK_KIND_MAGIC
} attack_kind_t;

/* Damage kind flags */
typedef enum {
    DAMAGE_NONE            = 0,
    DAMAGE_ACID            = 1 << 0,
    DAMAGE_BLUDGEONING     = 1 << 1,
    DAMAGE_COLD            = 1 << 2,
    DAMAGE_FIRE            = 1 << 3,
    DAMAGE_LIGHTNING       = 1 << 4,
    DAMAGE_PIERCING        = 1 << 5,
    DAMAGE_POISON          = 1 << 6,
    DAMAGE_SLASHING        = 1 << 7
} damage_flag_t;

typedef uint16_t damage_mask_t;

typedef struct {
    attack_kind_t attack_type;
    dice_kind_t damage_roll;
    damage_flag_t damage_kind;
    uint8_t range;
    int8_t hit_mod;     /* to hit modifier */
    int8_t damage_mod;  /* to damage modifier */
} attack_comp_t;

typedef attack_comp_t melee_components_t[MAX_ENTITIES]; 
typedef attack_comp_t ranged_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // ATTACK_COMP_H
