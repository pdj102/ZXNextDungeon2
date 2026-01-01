/**
 * @file location_comp.h
 * @author Paul Johnson
 * @brief location component for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOCATION_COMP_H
#define LOCATION_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/
typedef struct {
    coord_t  coord;
    entity_id_t next_in_location; /* next entity in the same location */
} location_comp_t;

typedef location_comp_t location_components_t[MAX_ENTITIES]; /* location component data */

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // LOCATION_COMP_H
