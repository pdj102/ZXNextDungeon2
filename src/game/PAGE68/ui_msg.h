/**
 * @file ui_msg_win.h
 * @author Paul Johnson
 * @brief Game UI_MSG_WIN
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UI_MSG_WIN_H
#define UI_MSG_WIN_H

#include <stdint.h>

#include "ecs/systems/PAGE42/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_msg_win_on_event(const event_t *event);

#endif // UI_MSG_WIN_H