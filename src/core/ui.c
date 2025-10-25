/**
 * @file ui.c
 * @author Paul  Johnson
 * @brief Game UI
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ui.h"

#include "../ecs/event_system.h"

#include "../game/global_state.h"
#include "../core/text.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/

 void ui_on_event(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val)
 {
    text_printf(&g.msg_win, "Event\n");
 }