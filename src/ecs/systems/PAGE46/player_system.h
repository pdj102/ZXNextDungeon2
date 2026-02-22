/**
 * @file player_system.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include "ecs/systems/PAGE42/event_system.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void player_system_init(void);
void player_system_handle_event(const event_t *event);
void player_system_update(void);

#endif // PLAYER_SYSTEM_H
