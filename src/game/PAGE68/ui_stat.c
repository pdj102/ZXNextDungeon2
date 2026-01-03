/**
 * @file ui_stat.c
 * @author Paul  Johnson
 * @brief Game UI_STAT
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/PAGE68/ui_stat.h"

#include "ecs/components/components.h"
#include "ecs/systems/systems_dispatch.h"

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
void ui_stat_win_on_event(event_t *event)
{
 switch( event->type )
    {
        case EVENT_NONE:
            break;
        case EVENT_ATTACKED:
        case EVENT_CONSUMED:
        case EVENT_DROPPED:
        case EVENT_EQUIPPED:
        case EVENT_UNEQUIPPED:
        case EVENT_PICKED_UP:
        case EVENT_ACTIVE_EFFECT_ATTACHED:
        case EVENT_ACTIVE_EFFECT_UNATTACHED:
        case EVENT_ACTIVE_EFFECT_EXPIRED:
        case EVENT_DAMAGED:
        case EVENT_DAMAGED_RESIST:
        case EVENT_DAMAGED_VULNERABLE:
        case EVENT_HEALED_HP:
        case EVENT_HEALED_MP:
            // TODO limit to only if the player is affected
            g.stat_win.dirty = 1;
            break;
        case EVENT_DIED:
        case EVENT_DAMAGED_IMMUNE:
            break;                        
        default:
            break;
    }    
}
void ui_stat_update_primary_stats(void)
{
    if (g.player.id == ENTITY_ID_INVALID)
        return;

    text_set_cursor(&g.stat_win, 0, 0);

    // TODO clear the lines

    text_printf(&g.stat_win, "STR:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_STR), system_effect_mod_sum(g.player.id, ATTRIBUTE_STR));
    text_printf(&g.stat_win, "DEX:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_DEX), system_effect_mod_sum(g.player.id, ATTRIBUTE_DEX));
    text_printf(&g.stat_win, "CON:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_CON), system_effect_mod_sum(g.player.id, ATTRIBUTE_CON));
    text_printf(&g.stat_win, "INT:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_INT), system_effect_mod_sum(g.player.id, ATTRIBUTE_INT));
    text_printf(&g.stat_win, "WIS:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_WIS), system_effect_mod_sum(g.player.id, ATTRIBUTE_WIS));
    text_printf(&g.stat_win, "CHA:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_CHA), system_effect_mod_sum(g.player.id, ATTRIBUTE_CHA));

}

void ui_stat_update_secondary_stats(void)
{
    if (g.player.id == ENTITY_ID_INVALID)
        return;

    text_set_cursor(&g.stat_win, 0, 7);
    text_printf(&g.stat_win, " AC:%u %d\n", system_stats_get_ac_base(g.player.id), system_effect_mod_sum(g.player.id, ATTRIBUTE_ARMOR_CLASS));
    text_printf(&g.stat_win, "SPD:%u %d\n", system_stats_get_speed_base(g.player.id), system_effect_mod_sum(g.player.id, ATTRIBUTE_SPEED));
}

void ui_stat_update_resource_stats(void)
{
    if (g.player.id == ENTITY_ID_INVALID)
        return;
        
    text_set_cursor(&g.stat_win, 0, 10);
    text_printf(&g.stat_win, "HP:%u/%u\n", system_stats_get_hp_max(g.player.id), system_stats_get_hp_cur(g.player.id));
    text_printf(&g.stat_win, "MP:\n");
}