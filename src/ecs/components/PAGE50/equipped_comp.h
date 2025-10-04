/**
 * @file equipped_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIPPED_COMP_H
#define EQUIPPED_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/


typedef struct {
    entity_id_t equipped_by;
} equipped_comp_t;

typedef equipped_comp_t equipped_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/
uint8_t equipped_add(entity_id_t entity, entity_id_t equipped_by);

void equipped_remove(entity_id_t entity);

#endif // EQUIPPED_COMP_H
