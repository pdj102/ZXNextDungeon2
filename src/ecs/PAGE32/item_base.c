/**
 * @file item_base.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "item_base.h"

#include "../item_comp.h"
#include "../item_comp_priv.h"

#include "../../game/global_state.h"

#include "../../core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const item_comp_base_t item_bases[ITEM_KIND_COUNT] = {
    [ITEM_NONE]   = { "None",   {' ', 0}, 0, 0, 0, 0 },
    [ITEM_SWORD]  = { "Sword",  {'s', 0}, 10, 2, 5, 20 },
    [ITEM_SHIELD] = { "Shield", {'s', 0}, 11, 3, 0, 15 },
    [ITEM_POTION] = { "Potion", {'p', 0}, 12, 1, 0, 5 },
    [ITEM_KEY]    = { "Key",    {'k', 0}, 13, 0, 0, 1 },
};

/***************************************************
 * public functions
 ***************************************************/

 void item_base_init(uint8_t item, uint8_t kind)
 {

 }

 void item_base_print_name(text_window_t *win, entity_id_t item)
 {
    item_kind_t kind = g.item_components[item].kind;
    text_print_string(win, item_bases[kind].name);
 }