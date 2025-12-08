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
    uint8_t  x; /* x coordinate on the map */
    uint8_t  y; /* y coordinate on the map */
    entity_id_t next_in_location; /* next entity in the same location */
} location_comp_t;

typedef location_comp_t location_components_t[MAX_ENTITIES]; /* location component data */

/***************************************************
 * public function prototypes
 ***************************************************/
void location_init(void);
bool_t location_add(entity_id_t entity, uint8_t x, uint8_t y);
void location_move(entity_id_t entity, uint8_t x, uint8_t y);
bool_t location_equal(entity_id_t entity1, entity_id_t entity2);
void location_remove(entity_id_t entity);

#endif // LOCATION_COMP_H
