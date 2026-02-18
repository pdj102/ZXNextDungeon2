/**
 * @file active_effect_comp.h
 * @author Paul Johnson
 * @brief Describes an active effect 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ACTIVE_EFFECT_COMP_H
#define ACTIVE_EFFECT_COMP_H

#include <stdint.h>

#include "ecs/components/effect_comp.h"

#include "core/util.h"

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/
#define MAX_ACTIVE_EFFECTS 4

/***************************************************
 * public types
 ***************************************************/

/* An active effect slot */
typedef struct {
    effect_t effect;            /* effect details */
    entity_id_t source;         /* effect source entity ID or INVALID_ENTITY_ID */
} active_effect_comp_t;

/* All entities' active effects in one flat struct, indexed by entity_id */
typedef struct {
    active_effect_comp_t slots[MAX_ENTITIES][MAX_ACTIVE_EFFECTS];
    uint8_t active_stack[MAX_ENTITIES][MAX_ACTIVE_EFFECTS];
    uint8_t head[MAX_ENTITIES];
} active_effect_components_t;

/***************************************************
 * public function prototypes
 ***************************************************/


#endif // ACTIVE_EFFECT_COMP_H
