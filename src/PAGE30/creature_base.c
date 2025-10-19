/**
 * @file creature_base.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma output CRT_ORG_PAGE_30 = 0xC000

#include "creature_base.h"

#include "../zxnext.h"

#include "../creature_comp.h"
#include "../creature_comp_priv.h"

#include "../text.h"
#include "../global_state.h"



/***************************************************
 * private variables
 * ***************************************************/
const creature_comp_base_t creature_bases[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE]   = { "None",   {' ', 0}, CREATURE_CLASS_NONE, 0, 0, 0 },
    [CREATURE_RAT]    = { "Rat",   {'R', 0}, CREATURE_CLASS_BEASTS, 12, 7, 10},
    [CREATURE_HUMAN]  = { "Human", {'H', 0}, CREATURE_CLASS_HUMANOIDS, 10, 4, 10}
};


/***************************************************
 * public functions
 ***************************************************/

 void test(void)
 {
    key_press();
 }