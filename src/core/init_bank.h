/**
 * @file init_bank.h
 * @author Paul Johnson
 * @brief Game INIT_BANK
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef INIT_BANK_H
#define INIT_BANK_H

#include <stdint.h>

#include "PAGE36/init.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

 void init_zxnext_bank(void);

void init_game_state_bank(void);

void init_ui_bank(void);


#endif // INIT_BANK_H