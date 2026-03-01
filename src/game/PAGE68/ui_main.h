/**
 * @file ui_main.h
 * @author Paul Johnson
 * @brief Game UI_MAIN
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <stdint.h>

#include "ecs/systems/PAGE42/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_main_win_on_event(const event_t *event);
void ui_main_update(void);

#endif // UI_MAIN_H