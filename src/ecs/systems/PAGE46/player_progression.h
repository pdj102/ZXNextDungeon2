/**
 * @file player_progression.h
 * @author Paul Johnson
 * @brief Player character creation, XP gain, and level-up
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef PLAYER_PROGRESSION_H
#define PLAYER_PROGRESSION_H

#include "ecs/systems/PAGE42/event_system.h"

/***************************************************
 * public function prototypes
 ***************************************************/
void player_progression_on_kill(const event_t *event);
void player_hunger_update(void);

#endif // PLAYER_PROGRESSION_H
