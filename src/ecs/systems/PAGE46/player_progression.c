/**
 * @file player_progression.c
 * @author Paul Johnson
 * @brief Player character creation, XP gain, and level-up
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ecs/systems/PAGE46/player_progression.h"

#include <stdint.h>

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"

#include "core/text.h"
#include "core/util.h"


/***************************************************
 * private defines
 ***************************************************/
#define PLAYER_MAX_LEVEL 10

/***************************************************
 * private variables
 ***************************************************/

/* XP awarded per challenge rating — D&D 5e values */
static const uint16_t s_cr_xp[] = {
    0,    /* CREATURE_CR_NONE */
    10,   /* CREATURE_CR_0   */
    25,   /* CREATURE_CR_1_8 */
    50,   /* CREATURE_CR_1_4 */
    100,  /* CREATURE_CR_1_2 */
    200,  /* CREATURE_CR_1   */
    450,  /* CREATURE_CR_2   */
    700,  /* CREATURE_CR_3   */
    1100, /* CREATURE_CR_4   */
    1800, /* CREATURE_CR_5   */
    2300, /* CREATURE_CR_6   */
    2900, /* CREATURE_CR_7   */
    3900, /* CREATURE_CR_8   */
};

/* XP required to reach each level — D&D 5e values (index = target level) */
static const uint16_t s_level_xp[] = {
    0,     /* 0 — unused */
    0,     /* 1 — start  */
    300,   /* 2          */
    900,   /* 3          */
    2700,  /* 4          */
    6500,  /* 5          */
    14000, /* 6          */
    23000, /* 7          */
    34000, /* 8          */
    48000, /* 9          */
    64000, /* 10 — max   */
};

/* Per-class stat gains applied on each level-up */
typedef struct {
    int8_t hp_per_level;
    int8_t mp_per_level;
} player_class_progression_t;

static const player_class_progression_t s_class_progression[PLAYER_CLASS_COUNT] = {
    [PLAYER_CLASS_FIGHTER] = { .hp_per_level = 10, .mp_per_level = 0 },
};

/***************************************************
 * public functions
 ***************************************************/
void player_progression_on_kill(const event_t *event)
{
    entity_id_t killed = event->target;
    creature_cr_t cr;
    uint16_t gain;

    if (!entity_has_component(killed, COMPONENT_CREATURE))
        return;

    cr = g.creature_components[killed].challenge;
    gain = s_cr_xp[cr];

    if (gain == 0)
        return;

    /* Add XP, guarding against uint16_t overflow at max level */
    if ((uint16_t)(g.player.xp + gain) < g.player.xp)
        g.player.xp = UINT16_MAX;
    else
        g.player.xp += gain;

    /* Level up while threshold is met and cap not reached */
    while (g.player.level < PLAYER_MAX_LEVEL &&
           g.player.xp >= s_level_xp[g.player.level + 1])
    {
        const player_class_progression_t *prog = &s_class_progression[g.player.class];
        g.player.level++;
        g.destructible_components[g.player.id].max_hp += prog->hp_per_level;
        g.player.max_mp += (uint8_t)prog->mp_per_level;
        if (g.player.cur_mp > g.player.max_mp) g.player.cur_mp = g.player.max_mp;
        g.player.proficiency_bonus = (uint8_t)((g.player.level - 1u) / 4u + 2u); /* L1-4=+2, L5-8=+3, L9-10=+4 */
        text_printf(&g.msg_win, "\nLevel up! You are now level %d.", (uint16_t)g.player.level);
    }

    g.stat_win.dirty = 1;
}

void player_hunger_update(void)
{
    if (g.player.hunger > 0)
        g.player.hunger--;

    switch (g.player.hunger)
    {
        case HUNGER_VERY_HUNGRY:
            text_printf(&g.msg_win, "\nYou are very hungry!");
            break;
        case HUNGER_HUNGRY:
            text_printf(&g.msg_win, "\nYou are hungry.");
            break;
        case 0:
            text_printf(&g.msg_win, "\nYou are starving!");
            system_damage_try_take_damage(g.player.id, ENTITY_ID_INVALID, 1, DAMAGE_NONE);
            break;
        default:
            break;
    }

    g.stat_win.dirty = 1;
}
