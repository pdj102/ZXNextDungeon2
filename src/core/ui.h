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

#include "../ecs/systems/PAGE42/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_on_event(const event_t event);

#endif // UI_H