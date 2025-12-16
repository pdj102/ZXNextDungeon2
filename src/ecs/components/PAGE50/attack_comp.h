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

#include "game/game.h"

#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef struct {
    attack_type_t attack_type;
    dice_roll_t damage_roll;
    damage_type_t damage_type;
    uint8_t range;
    int8_t hit_mod;     /* to hit modifier */
    int8_t damage_mod;  /* to damage modifier */
} attack_comp_t;

typedef attack_comp_t melee_components_t[MAX_ENTITIES]; 
typedef attack_comp_t ranged_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void attack_init(void);

void melee_add(entity_id_t entity, attack_comp_t melee_p);
void ranged_add(entity_id_t entity, attack_comp_t attack_p);

void melee_remove(entity_id_t entity);
void ranged_remove(entity_id_t entity);

#endif // ATTACK_COMP_H
