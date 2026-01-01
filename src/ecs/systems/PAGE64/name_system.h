/**
 * @file name_system.h
 * @author Paul Johnson
 * @brief name system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef NAME_SYSTEM_H
#define NAME_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/name_comp.h"

#include "core/text.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void name_system_print(text_window_t *win, name_id_t name);

#endif // NAME_SYSTEM_H
