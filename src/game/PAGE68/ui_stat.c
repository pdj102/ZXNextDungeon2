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

static const char * const cond_name[CONDITION_ID_COUNT] = {
    [CONDITION_ID_NONE]          = "",
    [CONDITION_ID_BLIND]         = "blinded",
    [CONDITION_ID_DEAF]          = "deafened",
    [CONDITION_ID_INCAPACITATED] = "incapac.",
    [CONDITION_ID_POISONED]      = "poisoned",
    [CONDITION_ID_CONFUSED]      = "confused",
};

/***************************************************
 * private function prototypes
 ***************************************************/

static void update_primary_stats(void);
static void update_secondary_stats(void);
static void update_resource_stats(void);
static void update_conditions(void);
static void update_game_info(void);

/***************************************************
 * Public functions
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
        case EVENT_CONDITION_APPLIED:
        case EVENT_CONDITION_REMOVED:
            if (event->source == g.player.id || event->target == g.player.id)
                g.stat_win.dirty = 1;
            break;
        case EVENT_TRANSITION:
        case EVENT_TRANSITION_TELEPORT:
                g.stat_win.dirty = 1;
            break;
        case EVENT_DIED:
        case EVENT_DAMAGED_IMMUNE:
            break;                        
        default:
            break;
    }    
}

void ui_stat_update(void)
{
    if (g.player.id == ENTITY_ID_INVALID)
        return;

    text_cls(&g.stat_win);        

    update_primary_stats();
    update_secondary_stats();
    update_resource_stats();
    update_conditions();
    update_game_info();
}

/***************************************************
 * Private functions
 ***************************************************/
/*
 * @brief Update primary stats (STR, DEX, CON, INT, WIS, CHA)
 */
void update_primary_stats(void)
{
    text_set_cursor(&g.stat_win, 0, 0);

    text_printf(&g.stat_win, "STR:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_STR), system_effect_mod_sum(g.player.id, ATTRIBUTE_STR));
    text_printf(&g.stat_win, "DEX:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_DEX), system_effect_mod_sum(g.player.id, ATTRIBUTE_DEX));
    text_printf(&g.stat_win, "CON:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_CON), system_effect_mod_sum(g.player.id, ATTRIBUTE_CON));
    text_printf(&g.stat_win, "INT:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_INT), system_effect_mod_sum(g.player.id, ATTRIBUTE_INT));
    text_printf(&g.stat_win, "WIS:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_WIS), system_effect_mod_sum(g.player.id, ATTRIBUTE_WIS));
    text_printf(&g.stat_win, "CHA:%u %C\n", system_stats_get_stat_base(g.player.id, STAT_CHA), system_effect_mod_sum(g.player.id, ATTRIBUTE_CHA));
}

/*
 * @brief Update secondary stats (PLayer level, XP, AC, Speed)
 */
void update_secondary_stats(void)
{
    text_set_cursor(&g.stat_win, 0, 7);

    text_printf(&g.stat_win, " AC:%u %d\n", system_stats_get_ac_base(g.player.id), system_effect_mod_sum(g.player.id, ATTRIBUTE_ARMOR_CLASS));
    text_printf(&g.stat_win, "SPD:%u %d\n", system_stats_get_speed_base(g.player.id), system_effect_mod_sum(g.player.id, ATTRIBUTE_SPEED));
}

/*
 * @brief Update resource stats (HP, MP)
 */
void update_resource_stats(void)
{       
    text_set_cursor(&g.stat_win, 0, 10);

    {
        uint8_t hp_cur = system_stats_get_hp_cur(g.player.id);
        uint8_t hp_max = system_stats_get_hp_max(g.player.id);
        if (hp_cur > (hp_max >> 1))
            text_printf(&g.stat_win, "%PGHP:%u/%u%PW\n", hp_cur, hp_max);
        else if (hp_cur > (hp_max >> 2))
            text_printf(&g.stat_win, "%PYHP:%u/%u%PW\n", hp_cur, hp_max);
        else
            text_printf(&g.stat_win, "%PRHP:%u/%u%PW\n", hp_cur, hp_max);
    }

    {
        uint8_t mp_cur = system_stats_get_mp_cur(g.player.id);
        uint8_t mp_max = system_stats_get_mp_max(g.player.id);
        if (mp_cur > (mp_max >> 1))
            text_printf(&g.stat_win, "%PBMP:%u/%u%PW\n", mp_cur, mp_max);
        else if (mp_cur > (mp_max >> 2))
            text_printf(&g.stat_win, "%PYMP:%u/%u%PW\n", mp_cur, mp_max);
        else
            text_printf(&g.stat_win, "%PRMP:%u/%u%PW\n", mp_cur, mp_max);
    }
    
    text_printf(&g.stat_win, "\nXP:%u\n", g.player.xp);
    text_printf(&g.stat_win, "LVL:%u\n", g.player.level);

}

/*
 * @brief Update conditions (e.g. poisoned, invisible)
 */ 
void update_conditions(void)
{
    uint8_t i;
    condition_mask_t mask;

    if (!entity_has_component(g.player.id, COMPONENT_CONDITION))
        return;

    text_set_cursor(&g.stat_win, 0, 12);

    mask = g.condition_components[g.player.id].conditions;
    for (i = 1; i < CONDITION_ID_COUNT; ++i)
    {
        if (mask & CONDITION_MASK(i))
        {
            if (i == CONDITION_ID_POISONED || i == CONDITION_ID_INCAPACITATED)
                text_printf(&g.stat_win, "%PR%s%PW\n", cond_name[i]);
            else
                text_printf(&g.stat_win, "%PY%s%PW\n", cond_name[i]);
        }
    }
}

/*
 * @brief Update game info (e.g. dungeon depth)
 */
void update_game_info(void)
{
    text_set_cursor(&g.stat_win, 0, 18);

    text_printf(&g.stat_win, "Depth: %u\n", g.depth);
}