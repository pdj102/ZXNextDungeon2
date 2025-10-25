/**
 * @file ui.h
 * @author Paul Johnson
 * @brief Game UI
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UI_H
#define UI_H

#include <stdint.h>

#include "../ecs/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_on_event(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val);

#endif // UI_H