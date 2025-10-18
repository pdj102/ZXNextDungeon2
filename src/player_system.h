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

#include <stdint.h>

#include "entity.h"
#include "zxnext.h"

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
void player_system_update(void);

#endif // PLAYER_SYSTEM_H
