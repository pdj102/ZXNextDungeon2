/**
 * @file ammo_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AMMO_COMP_H
#define AMMO_COMP_H

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/attack_comp.h"

#include "game/dice.h"

#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef struct {
    ammo_type_t ammo_type;
    dice_kind_t damage_roll;
    damage_flag_t damage_kind;
    int8_t damage_mod;
    int8_t hit_mod;
} ammo_comp_t;

typedef ammo_comp_t ammo_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // AMMO_COMP_H
