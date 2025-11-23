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

#include "../../../game/global_state.h"

#include "../../../core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const item_comp_base_t item_bases[ITEM_KIND_COUNT] = {
    [ITEM_NONE]             = { .class=ITEM_CLASS_NONE,     .name="None",           {.tile_id=' ',.tile_attr=0},   .weight=0,.value=0,.flags=0},
    [ITEM_CLUB]             = { .class=ITEM_CLASS_MELEE,    .name="Club",           {.tile_id='s', .tile_attr=0},  .weight=2, .value=1, .flags=0 },    
    [ITEM_SHORT_SWORD]      = { .class=ITEM_CLASS_MELEE,    .name="Short sword",    {.tile_id='s', .tile_attr=0},  .weight=2, .value=10, .flags=0 },
    [ITEM_LEATHER_ARMOUR]   = { .class=ITEM_CLASS_ARMOUR,   .name="Leather armour", {.tile_id='s', .tile_attr=0},  .weight=10, .value=10, .flags=0 },
    [ITEM_SHIELD]           = { .class=ITEM_CLASS_SHIELD,   .name="Shield",         {.tile_id='s', .tile_attr=0},  .weight=6, .value=10, .flags=0 },
    [ITEM_POTION_OF_HEALING]= { .class=ITEM_CLASS_POTION,   .name="Potion of healing", {.tile_id='p', .tile_attr=0}, .weight=1, .value=50, .flags=0 },
    [ITEM_KEY]              = { .class=ITEM_CLASS_KEY,      .name="Iron key",       {.tile_id='k', .tile_attr=0},   .weight=1, .value=0, .flags=0 },
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