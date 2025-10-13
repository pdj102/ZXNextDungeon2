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
bool_t player_ctrl_init_for_entity(entity_id_t entity);
void player_ctrl_destroy(entity_id_t id);

#endif // PLAYER_CTRL_COMP_H
