/**
 * @file item_base.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_BASE_H
#define ITEM_BASE_H

#include "../item_comp_priv.h"

#include "../../../core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
extern const item_comp_base_t item_bases[];

/***************************************************
 * public function prototypes
 ***************************************************/

void item_base_init(uint8_t item, uint8_t kind);

void item_base_print_name(text_window_t *win, entity_id_t item);

#endif // ITEM_BASE_H
