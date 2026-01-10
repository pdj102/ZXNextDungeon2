/**
 * @file openable_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef OPENABLE_COMP_H
#define OPENABLE_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Item component data per entity */
typedef struct {
    bool is_open;
} openable_comp_t;

typedef openable_comp_t openable_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // OPENABLE_COMP_H
