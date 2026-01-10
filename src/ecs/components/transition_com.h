/**
 * @file transition_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TRANSITION_COMP_H
#define TRANSITION_COMP_H

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/transition_com.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum 
{
    TRANSITION_NONE,
    TRANSITION_UP,
    TRANSITION_DOWN,
    TRANSITION_FALL,
    TRANSITION_TELEPORT,
} transistion_kind_t;

 /* Item component data per entity */
typedef struct {
    int8_t delta_depth;
    transistion_kind_t kind;
} transition_comp_t;

typedef transition_comp_t transition_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // TRANSITION_COMP_H
