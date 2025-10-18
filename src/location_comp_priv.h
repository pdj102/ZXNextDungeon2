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

typedef struct {
    uint8_t  x; /* x coordinate on the map */
    uint8_t  y; /* y coordinate on the map */
    entity_id_t next_in_location; /* next entity in the same location */
} location_comp_t;

typedef location_comp_t location_components_t[MAX_ENTITIES]; /* location component data */

/***************************************************
 * private function prototypes
 ***************************************************/


#endif // LOCATION_COMP_PRIV_H
