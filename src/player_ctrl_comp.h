/**
 * @file player_ctrl_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PLAYER_CTRL_COMP_H
#define PLAYER_CTRL_COMP_H

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
void player_ctrl_init(void);
bool_t player_add(entity_id_t entity);
void player_remove(entity_id_t entity);

#endif // PLAYER_CTRL_COMP_H
