/**
 * @file ui.c
 * @author Paul  Johnson
 * @brief Game UI
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "core/ui.h"

#include "../ecs/systems/PAGE42/event_system.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/game.h"
#include "game/global_state.h"

#include "core/text.h"

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
    // text_printf(&g.msg_win, "Event:%u src:%u tgt:%u val:%u\n", type, src, tgt, val);

    switch( type )
    {
        case EVENT_NONE:
            break;
        case EVENT_ATTACKED:
            system_monster_print_name(&g.msg_win, g.creature_components[src].kind);

            if (val == ATTACK_CRITICAL)
            {
                text_printf(&g.msg_win, " critically attacked ");
            } 
            else if (val == ATTACK_HIT)
            {
                text_printf(&g.msg_win, " attacked ");
            }
            else if (val == ATTACK_MISS)
            {
                text_printf(&g.msg_win, " missed ");    
            }
            system_monster_print_name(&g.msg_win, g.creature_components[tgt].kind);
            text_print_string(&g.msg_win, "\n");
            break;
        case EVENT_DIED:
            system_monster_print_name(&g.msg_win, g.creature_components[src].kind);
            text_printf(&g.msg_win, " died\n");
            break;
        case EVENT_DROPPED:
            system_monster_print_name(&g.msg_win, g.creature_components[src].kind);
            text_printf(&g.msg_win, " dropped ");
            system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
            text_print_string(&g.msg_win, "\n");            
            break;
        case EVENT_EQUIPPED:
            if (val == 1)
            {
                system_monster_print_name(&g.msg_win, g.creature_components[src].kind);
                text_printf(&g.msg_win, " equipped ");
                system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
                text_print_string(&g.msg_win, "\n");                
            } else
            {
                text_printf(&g.msg_win, "Unable to equip ");
                system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
                text_print_string(&g.msg_win, "\n");    
            }
            break;
        case EVENT_UNEQUIPPED:
            if (val == 1)
            {
                system_monster_print_name(&g.msg_win, g.creature_components[src].kind);
                text_printf(&g.msg_win, " unequipped ");
                system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
                text_print_string(&g.msg_win, "\n");                
            } else
            {
                text_printf(&g.msg_win, "Unable to unequip ");
                system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
                text_print_string(&g.msg_win, "\n");    
            }            
            break;
        case EVENT_PICKED_UP:
            system_monster_print_name(&g.msg_win, g.creature_components[src].kind);
            text_printf(&g.msg_win, " picked up ");
            system_item_print_name(&g.msg_win, g.item_components[tgt].kind);
            text_print_string(&g.msg_win, "\n");
            break;            
        default:
            break;
    }
 }