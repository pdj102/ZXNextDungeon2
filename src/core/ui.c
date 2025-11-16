/**
 * @file ui.c
 * @author Paul  Johnson
 * @brief Game UI
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ui.h"

#include "../ecs/systems/event_system.h"
#include "../ecs/components/creature_comp.h"
#include "../ecs/components/item_comp.h"

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
    text_printf(&g.msg_win, "Event:%u src:%u tgt:%u val:%u\n", type, src, tgt, val);

    switch( type )
    {
        case EVENT_NONE:
            break;
        case EVENT_PICKED_UP:
            creature_print_name(&g.msg_win, src);
            text_printf(&g.msg_win, " picked up ");
            item_print_name(&g.msg_win, tgt);
            text_print_string(&g.msg_win, "\n");
            break;
        case EVENT_DROPPED:
            creature_print_name(&g.msg_win, src);
            text_printf(&g.msg_win, " dropped ");
            item_print_name(&g.msg_win, tgt);
            text_print_string(&g.msg_win, "\n");            
            break;
        case EVENT_ATTACKED:
            creature_print_name(&g.msg_win, src);

            if (val == 1)
            {
                text_printf(&g.msg_win, " attacked ");
            } else
            {
                text_printf(&g.msg_win, " missed ");    
            }
            creature_print_name(&g.msg_win, tgt);
            text_print_string(&g.msg_win, "\n");
            break;
        case EVENT_DIED:
            creature_print_name(&g.msg_win, src);
            text_printf(&g.msg_win, " died\n");
            break;
        default:
            break;
    }
 }