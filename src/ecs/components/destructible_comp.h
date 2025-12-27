/**
 * @file destructible_comp.h
 * @author Paul Johnson
 * @brief Represents anything that can be targeted, has hit points and can be destroyed
 * 
 */

#ifndef DESTRUCTIBLE_COMP_H
#define DESTRUCTIBLE_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/game.h"

#include "core/text.h"
#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Creature destructible block */
typedef struct {
    int8_t ac;
    int8_t cur_hp;
    int8_t max_hp;
    damage_mask_t immune;
    damage_mask_t resist;
    damage_mask_t vulnerable;
} destructible_comp_t;


typedef destructible_comp_t destructible_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/


#endif // DESTRUCTIBLE_COMP_H
