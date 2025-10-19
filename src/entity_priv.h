/**
 * @file entity_priv.h
 * @author Paul Johnson
 * @brief Internal/private declarations for entity.c
 * 
 * @copyright Copyright (c) 2025
 *
 * This header exposes internal item definitions only to files that need them
 * (primarily `entity.c`). It should NOT be included by general modules. 
 */

#ifndef ENTITY_PRIV_H
#define ENTITY_PRIV_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * private defines
 ***************************************************/



/***************************************************
 * private types
 ***************************************************/

 /* Entity structure */
typedef struct { 
    uint16_t mask; /* component mask */
    uint8_t flags; /* entity flags */
} entity_t;

/* Entity arena structure - fast create and destroy */
typedef struct {
    entity_t entities[MAX_ENTITIES]; /* array of entities */
    entity_id_t free_ids[MAX_ENTITIES]; /* stack of free entity IDs */
    uint8_t free_head; /* index of the top of the free stack */
} entity_components_t;

/***************************************************
 * private function prototypes
 ***************************************************/


#endif // ENTITY_PRIV_H
