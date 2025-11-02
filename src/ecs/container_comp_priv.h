/**
 * @file container_comp_priv.h
 * @brief Private/internal declarations for container_comp.c
 *
 * This header exposes internal container definitions only to files that need them
 * (primarily `container_comp.c` and systems that operate on containers). It should NOT be included by general modules.
 */

#ifndef CONTAINER_COMP_PRIV_H
#define CONTAINER_COMP_PRIV_H

#include "entity.h"

#include "container_comp.h" 

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Container component data per entity */
typedef struct {
    entity_id_t head;   /* linked list head for entities within container */
    uint8_t capacity;   /* Maximum number of items in the container */
    uint8_t count;      /* Count of items in the container */
} container_comp_t;

typedef container_comp_t container_components_t[MAX_ENTITIES]; /* container component data */

#endif /* CONTAINER_COMP_PRIV_H */

