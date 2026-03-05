/**
 * @file consumable_comp.h
 * @author Paul Johnson
 * @brief ECS consumable component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONSUMABLE_COMP_H
#define CONSUMABLE_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    CONSUME_METHOD_NONE  = 0,
    CONSUME_METHOD_EAT   = 1,   /* food */
    CONSUME_METHOD_QUAFF = 2,   /* potions */
} consume_method_t;

typedef struct {
    consume_method_t method;
} consumable_comp_t;

typedef consumable_comp_t consumable_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // CONSUMABLE_COMP_H
