/**
 * @file contained_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONTAINED_COMP_H
#define CONTAINED_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Contained component data per entity */
typedef struct {
    entity_id_t container; /* the container entity that contains this one */
    entity_id_t next; /* next entity in the container */
} contained_comp_t;

typedef contained_comp_t contained_components_t[MAX_ENTITIES]; /* contained component data */

/***************************************************
 * public function prototypes
 ***************************************************/
void contained_add(entity_id_t entity, entity_id_t container, entity_id_t next);
void contained_remove(entity_id_t entity);

#endif // CONTAINED_COMP_H
