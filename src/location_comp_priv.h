/**
 * @file location_comp_priv.h
 * @author Paul Johnson
 * @brief Private/internal declarations for location_comp.c
 * 
 * @copyright Copyright (c) 2025
 * 
 * This header exposes internal item definitions only to files that need them
 * (primarily `location_comp.c`). It should NOT be included by general modules.
 * 
 */

#ifndef LOCATION_COMP_PRIV_H
#define LOCATION_COMP_PRIV_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * private types
 ***************************************************/
typedef enum {
    LOC_NONE,           // entity is not placed
    LOC_MAP,            // entity is on the map
    LOC_CONTAINER       // entity is contained in another entity
} location_comp_type_t;

typedef struct {
    location_comp_type_t type;   /* type of location */
    union {
        struct {
            uint8_t  x; /* x coordinate on the map */
            uint8_t  y; /* y coordinate on the map */
        } map;
        entity_id_t container; /* entity containing this entity */
    } data;
    entity_id_t next_in_location; /* next entity in the same location either container or map cell */
} location_comp_t;

typedef location_comp_t location_components_t[MAX_ENTITIES]; /* location component data */



/***************************************************
 * private function prototypes
 ***************************************************/


#endif // LOCATION_COMP_PRIV_H
