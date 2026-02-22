/**
 * @file ui_msg_win.c
 * @author Paul  Johnson
 * @brief Game UI_MSG_WIN
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/PAGE68/ui_msg.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/components/components.h"

#include "ecs/components/condition_comp.h"

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

  /* Subject is the player e.g. "You attack the goblin." */
 static const char *verb_present_tense[] = {
    [EVENT_NONE]                    = "",
    [EVENT_ATTACKED]                = " attack ",
    [EVENT_ATTACKED_AND_MISSED]     = " miss ",    
    [EVENT_ATTACKED_AND_CRITICAL]   = " critically attack ",
    [EVENT_BUMPED]                  = " bump ",
    [EVENT_CONSUMED]                = " consume ",
    [EVENT_DAMAGED]                 = " take %d damage",
    [EVENT_DAMAGED_IMMUNE]          = " are immune!",
    [EVENT_DAMAGED_RESIST]          = " resist and take %d damage",
    [EVENT_DAMAGED_VULNERABLE]      = " are vulnerable and take %d damage",
    [EVENT_KILLED]                  = " kill ",
    [EVENT_DIED]                    = " died!",
    [EVENT_DROPPED]                 = " drop ",
    [EVENT_EQUIPPED]                = " equip ",
    [EVENT_PICKED_UP]               = " pickup ",
    [EVENT_STOOD_ON]                = " stood on ",
    [EVENT_UNEQUIPPED]              = " unequip ",
    [EVENT_HEALED_HP]               = " restore %d health",
    [EVENT_HEALED_MP]               = " restore %d mana",
    [EVENT_SPOTTED_TARGET]          = " see ",
};
 
 /* Subject is third person singular e.g. "The goblin attacks you." */
 static const char *verb_third_person_singular[] = {
    [EVENT_NONE]                    = "",
    [EVENT_ATTACKED]                = " attacks ",
    [EVENT_ATTACKED_AND_MISSED]     = " misses ",    
    [EVENT_ATTACKED_AND_CRITICAL]   = " critically attacks ",
    [EVENT_BUMPED]                  = " bumps ",
    [EVENT_CONSUMED]                = " consumes ",
    [EVENT_DAMAGED]                 = " takes %d damage",
    [EVENT_DAMAGED_IMMUNE]          = " is immune!",
    [EVENT_DAMAGED_RESIST]          = " resists and takes %d damage",
    [EVENT_DAMAGED_VULNERABLE]      = " is vulnerable and takes %d damage",
    [EVENT_DIED]                    = " dies!",

    [EVENT_DROPPED]                 = " drops ",
    [EVENT_EQUIPPED]                = " equips ",
    [EVENT_PICKED_UP]               = " pickups ",
    [EVENT_STOOD_ON]                = " stands on ",
    [EVENT_UNEQUIPPED]              = " unequips ",
    [EVENT_HEALED_HP]               = " restores %d health",
    [EVENT_HEALED_MP]               = " restores %d mana",
    [EVENT_SPOTTED_TARGET]          = " sees ",
};



/* Condition descriptions — indexed by condition_id_t, used in applied/removed messages */
static const char *condition_name[] = {
    [CONDITION_ID_NONE]          = "",
    [CONDITION_ID_BLIND]         = "blinded",
    [CONDITION_ID_DEAF]          = "deafened",
    [CONDITION_ID_INCAPACITATED] = "incapacitated",
    [CONDITION_ID_POISONED]      = "poisoned",
    [CONDITION_ID_CONFUSED]      = "confused",
};

/***************************************************
 * private function prototypes
 ***************************************************/
static void ui_msg_win_print_subject(entity_id_t e);

static void ui_msg_win_print_verb(event_type_t type, bool subject_is_player);

static void ui_msg_win_print_object(entity_id_t e);

static bool ui_msg_win_is_player(entity_id_t e);

static void ui_msg_win_nl(void);

/***************************************************
 * functions
 ***************************************************/

 void ui_msg_win_on_event(const event_t *event)
  {
    bool source_is_player = ui_msg_win_is_player(event->source);
    bool target_is_player = ui_msg_win_is_player(event->target);

    switch( event->type )
    {
        case EVENT_NONE:
            break;
        case EVENT_ATTACKED:
        case EVENT_ATTACKED_AND_CRITICAL:
        case EVENT_ATTACKED_AND_MISSED:
        case EVENT_CLOSED:
        case EVENT_CONSUMED:
        case EVENT_DROPPED:
        case EVENT_EQUIPPED:
        case EVENT_UNEQUIPPED:
        case EVENT_OPENED:
        case EVENT_PICKED_UP:
        case EVENT_SPOTTED_TARGET:
        case EVENT_KILLED:
            /* [Source] [Verb] [Target] e.g. You kill goblin or Goblin kills you. */
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->source);
            ui_msg_win_print_verb(event->type, source_is_player);
            ui_msg_win_print_object(event->target);
            break;
        case EVENT_DIED:
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->source);
            ui_msg_win_print_verb(event->type, source_is_player);
            break;
        case EVENT_DAMAGED_IMMUNE:
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->target);
            ui_msg_win_print_verb(event->type, target_is_player);
            break;
        case EVENT_DAMAGED:
        case EVENT_DAMAGED_RESIST:
        case EVENT_DAMAGED_VULNERABLE:
        case EVENT_HEALED_HP:
        case EVENT_HEALED_MP:
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->target);
            if (target_is_player)
            {
                text_printf(&g.msg_win, verb_present_tense[event->type], event->value);
            }
            else
            {
                text_printf(&g.msg_win, verb_third_person_singular[event->type], event->value);
            }
            break;
        case EVENT_ACTIVE_EFFECT_ATTACHED:
            util_info("Active effect attached");
            break;
        case EVENT_ACTIVE_EFFECT_UNATTACHED:
            util_info("Active effect unattached");
            break;
        case EVENT_ACTIVE_EFFECT_EXPIRED:
            util_info("Active effect expired");
            break;
        case EVENT_CONDITION_APPLIED:
        {
            condition_id_t cid = (condition_id_t)event->value;
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->target);
            if (target_is_player)
                text_printf(&g.msg_win, " are %s!", condition_name[cid]);
            else
                text_printf(&g.msg_win, " is %s!", condition_name[cid]);
            break;
        }
        case EVENT_CONDITION_REMOVED:
        {
            condition_id_t cid = (condition_id_t)event->value;
            ui_msg_win_nl();
            ui_msg_win_print_subject(event->target);
            if (target_is_player)
                text_printf(&g.msg_win, " are no longer %s.", condition_name[cid]);
            else
                text_printf(&g.msg_win, " is no longer %s.", condition_name[cid]);
            break;
        }
        case EVENT_TRANSITION:
            text_printf(&g.msg_win, "Transitioning...");
            break;
        default:
            break;
    }
 }

static void ui_msg_win_print_subject(entity_id_t e)
{
    if (ui_msg_win_is_player(e))
        text_print_string(&g.msg_win, "You");
    else
        system_name_print(&g.msg_win, g.name_components[e]);
}

static void ui_msg_win_print_object(entity_id_t e)
{
    if (ui_msg_win_is_player(e))
        text_print_string(&g.msg_win, "you");
    else
    {
        system_name_print(&g.msg_win, g.name_components[e]);
    }
}

static void ui_msg_win_print_verb(event_type_t type, bool subject_is_player)
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

static bool ui_msg_win_is_player(entity_id_t e)
{
    return (e == g.player.id);
}

static void ui_msg_win_nl(void)
{
    text_print_string(&g.msg_win, "\n");
}
