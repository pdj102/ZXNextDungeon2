/**
 * @file player_factory.c
 * @author Paul Johnson
 * @brief Player character creation and initialisation
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "player_factory.h"

#include <stdint.h>
#include <stdbool.h>      /* bool */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE46/player_progression.h"
#include "game/global_state.h"
#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private variables
 ***************************************************/

static const char * const s_class_names[PLAYER_CLASS_COUNT] = {
    [PLAYER_CLASS_FIGHTER] = "Fighter",
};

static const char * const s_attr_names[ATTRIBUTE_COUNT] = {
    [ATTRIBUTE_NONE]         = "none",
    [ATTRIBUTE_CUR_HP]       = "HP",
    [ATTRIBUTE_CUR_MP]       = "MP",
    [ATTRIBUTE_MAX_HP]       = "MaxHP",
    [ATTRIBUTE_MAX_MP]       = "MaxMP",
    [ATTRIBUTE_STR]          = "STR",
    [ATTRIBUTE_DEX]          = "DEX",
    [ATTRIBUTE_CON]          = "CON",
    [ATTRIBUTE_INT]          = "INT",
    [ATTRIBUTE_WIS]          = "WIS",
    [ATTRIBUTE_CHA]          = "CHA",
    [ATTRIBUTE_ARMOR_CLASS]  = "AC",
    [ATTRIBUTE_SPEED]        = "SPD",
    [ATTRIBUTE_ATTACK]       = "ATK",
    [ATTRIBUTE_DAMAGE]       = "DMG",
    [ATTRIBUTE_HUNGER]       = "Hunger",
};

static const char * const s_cond_names[CONDITION_ID_COUNT] = {
    [CONDITION_ID_NONE]          = "",
    [CONDITION_ID_BLIND]         = "blinded",
    [CONDITION_ID_DEAF]          = "deafened",
    [CONDITION_ID_INCAPACITATED] = "incapac.",
    [CONDITION_ID_POISONED]      = "poisoned",
    [CONDITION_ID_CONFUSED]      = "confused",
};

/***************************************************
 * public functions
 ***************************************************/
entity_id_t player_factory_create(void)
{
    entity_id_t e;

    /* Create player entity */
    g.player.id = ENTITY_ID_INVALID;
    e = system_monster_create_player();
    util_assert(e != ENTITY_ID_INVALID);
    g.player.id = e;

    /* ==== initialise a default player ===*/
    g.player.xp                = 0;
    g.player.level             = 1;
    g.player.class             = PLAYER_CLASS_FIGHTER;
    g.player.gold              = 0;
    g.player.hunger            = HUNGER_MAX;  /* Start satiated */
    g.player.cur_mp            = 0;
    g.player.max_mp            = 0;
    g.player.proficiency_bonus = 2;           /* D&D 5e: +2 at level 1 */

    return e;
}

void player_factory_show(void)
{
    uint8_t i;
    entity_id_t entity = g.player.id;
    int key;

    text_cls(&g.main_win);

    /* --- Row 0: Class + Level --- */
    text_set_cursor(&g.main_win, 0, 0);
    text_printf(&g.main_win, "%s          Lvl: %u\n",
        s_class_names[g.player.class], (uint16_t)g.player.level);

    /* --- Row 1: XP + Gold --- */
    text_printf(&g.main_win, "XP: %U      Gold: %U\n", g.player.xp, g.player.gold);

    /* --- Row 2: Proficiency Bonus --- */
    text_printf(&g.main_win, "Prof: +%u\n", (uint16_t)g.player.proficiency_bonus);

    /* --- Rows 4-9: Primary stats --- */
    {
        static const stat_kind_t s_primary[STAT_COUNT] = {
            STAT_STR, STAT_DEX, STAT_CON, STAT_INT, STAT_WIS, STAT_CHA
        };
        static const char * const s_stat_labels[STAT_COUNT] = {
            "STR", "DEX", "CON", "INT", "WIS", "CHA"
        };

        for (i = 0; i < STAT_COUNT; ++i)
        {
            uint8_t base = system_stats_get_stat_base(entity, s_primary[i]);
            int8_t  mod  = system_effect_mod_sum(entity, (attribute_t)(ATTRIBUTE_STR + i));
            text_set_cursor(&g.main_win, 0, (uint8_t)(4 + i));
            text_printf(&g.main_win, "%s: %u %C", s_stat_labels[i], base, mod);
        }
    }

    /* --- Rows 4-5: Secondary stats (right column) --- */
    {
        uint8_t ac_base  = system_stats_get_ac_base(entity);
        int8_t  ac_mod   = system_effect_mod_sum(entity, ATTRIBUTE_ARMOR_CLASS);
        uint8_t spd_base = system_stats_get_speed_base(entity);
        int8_t  spd_mod  = system_effect_mod_sum(entity, ATTRIBUTE_SPEED);

        text_set_cursor(&g.main_win, 16, 4);
        text_printf(&g.main_win, " AC: %u %C", ac_base, ac_mod);
        text_set_cursor(&g.main_win, 16, 5);
        text_printf(&g.main_win, "SPD: %u %C", spd_base, spd_mod);
    }

    /* --- Row 11: HP / MP --- */
    {
        uint8_t hp_cur = system_stats_get_hp_cur(entity);
        uint8_t hp_max = system_stats_get_hp_max(entity);
        uint8_t mp_cur = system_stats_get_mp_cur(entity);
        uint8_t mp_max = system_stats_get_mp_max(entity);

        text_set_cursor(&g.main_win, 0, 11);
        text_printf(&g.main_win, "HP: %u/%u   MP: %u/%u", hp_cur, hp_max, mp_cur, mp_max);
    }

    /* --- Row 13: Hunger status --- */
    text_set_cursor(&g.main_win, 0, 13);
    if (g.player.hunger == 0)
        text_printf(&g.main_win, "%PRSTARVING%PW");
    else if (g.player.hunger <= HUNGER_VERY_HUNGRY)
        text_printf(&g.main_win, "%PRVery Hungry%PW");
    else if (g.player.hunger <= HUNGER_HUNGRY)
        text_printf(&g.main_win, "%PYHungry%PW");
    else if (g.player.hunger <= HUNGER_SATISFIED)
        text_printf(&g.main_win, "Satisfied");
    else
        text_printf(&g.main_win, "%PGSatiated%PW");

    /* --- Row 15: Active Effects --- */
    text_set_cursor(&g.main_win, 0, 15);
    text_printf(&g.main_win, "Active Effects:\n");
    {
        uint8_t count = system_effect_get_count(entity);
        if (count == 0)
        {
            text_printf(&g.main_win, " (none)");
        }
        else
        {
            for (i = 0; i < count; ++i)
            {
                effect_t e;
                entity_id_t src;
                system_effect_get_at(entity, i, &e, &src);

                if (e.kind == EFFECT_STAT_MODIFIER)
                {
                    text_printf(&g.main_win, " %s %C\n",
                        s_attr_names[e.stat.attribute], e.stat.magnitude);
                }
                else if (e.kind == EFFECT_APPLY_CONDITION)
                {
                    text_printf(&g.main_win, " +%s\n", s_cond_names[e.condition]);
                }
                else if (e.kind == EFFECT_REMOVE_CONDITION)
                {
                    text_printf(&g.main_win, " -%s\n", s_cond_names[e.condition]);
                }
            }
        }
    }

    /* --- Row 20: Conditions --- */
    text_set_cursor(&g.main_win, 0, 20);
    text_printf(&g.main_win, "Conditions:\n");
    if (entity_has_component(entity, COMPONENT_CONDITION))
    {
        condition_mask_t mask = g.condition_components[entity].conditions;
        uint8_t found = 0;
        for (i = 1; i < CONDITION_ID_COUNT; ++i)
        {
            if (mask & CONDITION_MASK(i))
            {
                if (i == CONDITION_ID_POISONED || i == CONDITION_ID_INCAPACITATED)
                    text_printf(&g.main_win, " %PR%s%PW\n", s_cond_names[i]);
                else
                    text_printf(&g.main_win, " %PY%s%PW\n", s_cond_names[i]);
                found = 1;
            }
        }
        if (!found)
            text_printf(&g.main_win, " (none)");
    }
    else
    {
        text_printf(&g.main_win, " (none)");
    }

    /* --- Row 23: Prompt --- */
    text_set_cursor(&g.main_win, 0, 23);
    text_print_string(&g.main_win, "Press any key...");

    key = key_press();

    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}
