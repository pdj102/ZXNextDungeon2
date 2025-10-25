/**
 * @file creature_base.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CREATURE_BASE_H
#define CREATURE_BASE_H

#include "../creature_comp_priv.h"

#include "../../core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
extern const creature_comp_base_t creature_bases[];

/***************************************************
 * public function prototypes
 ***************************************************/

void creature_base_init(uint8_t creature, uint8_t kind);

void creature_base_print_name(text_window_t *win, entity_id_t creature);

#endif // CREATURE_BASE_H
