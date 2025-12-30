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

#include "ecs/systems/PAGE42/event_system.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_on_event(const event_t *event);

void ui_update_primary_stats(void);
void ui_update_secondary_stats(void);
void ui_update_resource_stats(void);

#endif // UI_H