/**
 * @file player_system_priv.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PLAYER_SYSTEM_PRIV_H
#define PLAYER_SYSTEM_PRIV_H

#include "../entity.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
void melee_attack(void);
void pickup(void);
void drop(void);
void inventory(void);
void display_inventory(void);
int8_t prompt_letter(uint8_t max_index);

#endif // PLAYER_SYSTEM_PRIV_H
