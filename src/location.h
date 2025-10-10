/**
 * @file location.h
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    LOC_NONE,       // entity is not placed
    LOC_MAP,        // entity is on the map
    LOC_CONTAINER      // entity is contained in another entity
} location_type_t;

typedef struct {
    location_type_t type;   /* type of location */
    union {
        struct {
            uint8_t  x; /* x coordinate on the map */
            uint8_t  y; /* y coordinate on the map */
        } map;
        entity_id_t container; /* entity containing this entity */
    } data;
    entity_id_t next_in_location; /* next entity in the same location either container or map cell */
} location_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void place_on_map(entity_id_t entity, uint8_t x, uint8_t y);
void place_in_container(entity_id_t entity, entity_id_t container);
void remove_from_map(entity_id_t entity);
void remove_from_container(entity_id_t entity);
void remove_from_current_location(entity_id_t entity);

#endif // LOCATION_H
