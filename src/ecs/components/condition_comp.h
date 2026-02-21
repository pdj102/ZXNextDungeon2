/**
 * @file condition_comp.h
 * @author Paul Johnson
 * @brief Condition component — bitmask of active conditions on an entity
 *
 * Conditions are bestowed via EFFECT_APPLY_CONDITION effects.
 * The condition_id_t value is stored in effect_t.magnitude.
 * Duration is handled by the active-effect system (PAGE60).
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CONDITION_COMP_H
#define CONDITION_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/* Convert a condition_id_t to its bitmask */
#define CONDITION_MASK(id)  ((condition_mask_t)(1u << (uint8_t)(id)))

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    CONDITION_ID_NONE          = 0,
    CONDITION_ID_BLIND,             /* cannot see */
    CONDITION_ID_DEAF,              /* cannot hear */
    CONDITION_ID_INCAPACITATED,     /* cannot act */
    CONDITION_ID_POISONED,          /* takes damage each turn */
    CONDITION_ID_CONFUSED,          /* random movement */
    CONDITION_ID_COUNT              /* must be <= 8 to fit condition_mask_t */
} condition_id_t;

typedef uint8_t condition_mask_t;   /* bit N set = CONDITION_ID N is active */

typedef struct {
    condition_mask_t conditions;
} condition_comp_t;

typedef condition_comp_t condition_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // CONDITION_COMP_H
