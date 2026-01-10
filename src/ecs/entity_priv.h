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

#include "ecs/entity.h"

/***************************************************
 * private defines
 ***************************************************/
#define COMPONENT_BYTES ((COMPONENT_MAX + 7) >> 3)


/***************************************************
 * private types
 ***************************************************/

typedef struct {
    uint8_t mask[COMPONENT_BYTES];
} component_mask_t;


 /* Entity structure */
typedef struct { 
    component_mask_t components; /* component mask */
    uint8_t flags;              /* entity flags */
} entity_t;

/* Entites and fast iterate lists */
typedef struct {
    entity_t    entities[MAX_ENTITIES];     /* array of entities */

    entity_id_t active_list[MAX_ENTITIES];  /* stack of active entities */
    uint8_t     active_head;               /* number of active entities */
    entity_id_t destroy_list[MAX_ENTITIES]; /* stack of entities marked for destruction */
    uint8_t     destroy_head;              /* number of entities marked for destruction */
} entity_components_t;

/***************************************************
 * private function prototypes
 ***************************************************/


#endif // ENTITY_PRIV_H
