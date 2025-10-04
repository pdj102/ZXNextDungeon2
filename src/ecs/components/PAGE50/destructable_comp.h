/**
 * @file destructable_comp.h
 * @author Paul Johnson
 * @brief Represents anything that can be targeted, has hit points and can be destroyed
 * 
 */

#ifndef DESTRUCTABLE_COMP_H
#define DESTRUCTABLE_COMP_H

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
/* Creature destructable block */
typedef struct {
    int8_t ac;
    int8_t cur_hp;
    int8_t max_hp;
    uint8_t immune_types;
    uint8_t resistance_types;
    uint8_t vuln_types;
} destructable_comp_t;


typedef destructable_comp_t destructable_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void destructable_add(entity_id_t entity, const destructable_comp_t destructable);

void destructable_remove(entity_id_t entity);

#endif // DESTRUCTABLE_COMP_H
