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

#include "ecs/components/components.h"

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

 /* Subject is the player */
 static const char *verb_present_tense[] = {
    [EVENT_NONE]                    = "",
    [EVENT_ATTACKED]                = " attack ",
    [EVENT_ATTACKED_AND_MISSED]     = " miss ",    
    [EVENT_ATTACKED_AND_CRITICAL]   = " critically attack ",
    [EVENT_BUMPED]                  = " bumped ",
    [EVENT_CONSUMED]                = " consume ",
    [EVENT_DAMAGED]                 = " take %d damage\n",
    [EVENT_DAMAGED_IMMUNE]          = " are immune!\n",
    [EVENT_DAMAGED_RESIST]          = " resist and take %d damage\n",
    [EVENT_DAMAGED_VULNERABLE]      = " are vulnerable and take %d damage\n",
    [EVENT_DIED]                    = " died!\n",
    [EVENT_DROPPED]                 = " drop ",
    [EVENT_EQUIPPED]                = " equip ",
    [EVENT_PICKED_UP]               = " pickup ",
    [EVENT_STOOD_ON]                = " stood on ",
    [EVENT_UNEQUIPPED]              = " unequip "
};

 /* Third person singular */
 static const char *verb_third_person_singular[] = {
    [EVENT_NONE]                    = "",
    [EVENT_ATTACKED]                = " attacks ",
    [EVENT_ATTACKED_AND_MISSED]     = " misses ",    
    [EVENT_ATTACKED_AND_CRITICAL]   = " critically attacks ",
    [EVENT_BUMPED]                  = " bumps ",
    [EVENT_CONSUMED]                = " consumes ",
    [EVENT_DAMAGED]                 = " takes %d damage\n",
    [EVENT_DAMAGED_IMMUNE]          = " is immune!\n",
    [EVENT_DAMAGED_RESIST]          = " resists and takes %d damage\n",
    [EVENT_DAMAGED_VULNERABLE]      = " is vulnerable and takes %d damage\n",
    [EVENT_DIED]                    = " dies!\n",
    [EVENT_DROPPED]                 = " drops ",
    [EVENT_EQUIPPED]                = " equips ",
    [EVENT_PICKED_UP]               = " pickups ",
    [EVENT_STOOD_ON]                = " stands on ",
    [EVENT_UNEQUIPPED]              = " unequips "    
};



/***************************************************
 * private function prototypes
 ***************************************************/
static void ui_print_subject(entity_id_t e);

static void ui_print_verb(event_type_t type, bool_t subject_is_player);

static void ui_print_object(entity_id_t e);

static bool_t ui_is_player(entity_id_t e);

static void ui_nl(void);

/***************************************************
 * functions
 ***************************************************/

 void ui_on_event(const event_t event)
 {
    bool_t subject_is_player = ui_is_player(event.source);

    switch( event.type )
    {
        case EVENT_NONE:
            break;
        case EVENT_ATTACKED:
        case EVENT_CONSUMED:
        case EVENT_DROPPED:
        case EVENT_EQUIPPED:
        case EVENT_UNEQUIPPED:
        case EVENT_PICKED_UP:
            ui_print_subject(event.source);
            ui_print_verb(event.type, subject_is_player);
            ui_print_object(event.target);
            break;
        case EVENT_DIED:
        case EVENT_DAMAGED_IMMUNE:
            ui_print_subject(event.source);
            ui_print_verb(event.type, subject_is_player);
            break;
        case EVENT_DAMAGED:
        case EVENT_DAMAGED_RESIST:
        case EVENT_DAMAGED_VULNERABLE:
            ui_print_subject(event.source);
            if (subject_is_player)
            {
                text_printf(&g.msg_win, verb_present_tense[event.type], event.value);
            }
            else
            {
                text_printf(&g.msg_win, verb_third_person_singular[event.type], event.value);
            }
            break;            
        default:
            break;
    }
    ui_nl();
 }

static void ui_print_subject(entity_id_t e)
{
    if (ui_is_player(e))
        text_print_string(&g.msg_win, "You");
    else
        system_name_print(&g.msg_win, g.name_components[e]);
}

static void ui_print_object(entity_id_t e)
{
    if (ui_is_player(e))
        text_print_string(&g.msg_win, "you");
    else
    {
        system_name_print(&g.msg_win, g.name_components[e]);
    }
}

static void ui_print_verb(event_type_t type, bool_t subject_is_player)
{
    if (subject_is_player)
    {
        text_print_string(&g.msg_win, verb_present_tense[type]);
    }
    else
    {
        text_print_string(&g.msg_win, verb_third_person_singular[type]);
    }
}

static bool_t ui_is_player(entity_id_t e)
{
    return (e == g.player.id);
}

static void ui_nl(void)
{
    text_print_string(&g.msg_win, "\n");
}
