/**
 * @file stackable_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef STACKABLE_COMP_H
#define STACKABLE_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Item component data per entity */
typedef struct {
    uint8_t quantity;    /* stack size */
} stackable_comp_t;

typedef stackable_comp_t stackable_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void stackable_consume_or_destroy(entity_id_t entity);

#endif // STACKABLE_COMP_H
