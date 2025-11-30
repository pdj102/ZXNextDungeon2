/**
 * @file contained_comp_priv.h
 * @brief Private/internal declarations for contained_comp.c
 *
 * This header exposes internal contained definitions only to files that need them
 * (primarily `contained_comp.c` and systems that operate on containeds). It should NOT be included by general modules.
 */

#ifndef CONTAINED_COMP_PRIV_H
#define CONTAINED_COMP_PRIV_H

#include "ecs/entity.h"

#include "ecs/components/contained_comp.h" 

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Contained component data per entity */
typedef struct {
    entity_id_t container; /* the container entity that contains this one */
    entity_id_t next; /* next entity in the container */
} contained_comp_t;

typedef contained_comp_t contained_components_t[MAX_ENTITIES]; /* contained component data */

#endif /* CONTAINED_COMP_PRIV_H */

