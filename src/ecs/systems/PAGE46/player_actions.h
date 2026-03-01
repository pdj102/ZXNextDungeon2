/**
 * @file player_actions.h
 * @author Paul Johnson
 * @brief Player world-interaction action implementations
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef PLAYER_ACTIONS_H
#define PLAYER_ACTIONS_H

/***************************************************
 * public function prototypes
 ***************************************************/
void player_action_climb(void);
void player_action_close(void);
void player_action_melee_attack(void);
void player_action_open(void);
void player_action_pickup(void);
void player_action_target(void);
void player_action_look(void);

#endif // PLAYER_ACTIONS_H
