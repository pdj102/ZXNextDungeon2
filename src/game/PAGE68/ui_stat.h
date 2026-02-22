/**
 * @file ui_stat.h
 * @author Paul Johnson
 * @brief Game UI_STAT
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UI_STAT_H
#define UI_STAT_H

#include <stdint.h>

#include "ecs/systems/PAGE42/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_stat_win_on_event(const event_t *event);
void ui_stat_update(void);

#endif // UI_STAT_H