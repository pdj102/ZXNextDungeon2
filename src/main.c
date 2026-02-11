/**
 * @file main.c
 * @author Paul Johnson
 * @brief ZX Next Dungeon II
 * @version 0.1

 *
 * @copyright Copyright (c) 2025
 *
 */

#include <arch/zxn.h>

#include "main.h"

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/ui.h"
#include "game/map.h"
#include "game/map_render.h"
#include "game/global_state.h"
#include "game/world.h"
#include "game/PAGE34/dungeon_gen.h"

#include "core/util.h"
#include "core/text.h"

#define STACK_LOW 0xBF00
#define STACK_HIGH 0xBFFF
#define STACK_PATTERN 0xCD

static uint16_t stack_max_usage(void);
static void turn(void);
static void process_entity_turn(entity_id_t id);

static void map(void);

int main(void)
{
    uint16_t stack_max;
    uint16_t stack;

    /* Stack guard */
    uint8_t *p = (uint8_t *)STACK_LOW;
    while ((uintptr_t)p < STACK_HIGH)
        *p++ = STACK_PATTERN;

    stack_max = 0;
    stack = 0;

    zxnext_init();
    ui_init();
    
    util_info("Debug build");
    text_printf(&g.msg_win, "\nGlobal size:%U", sizeof(g));
    util_assert(sizeof(g) < 0x3FFF);

    new_game();

    map_render();

    ui_update_primary_stats();
    ui_update_secondary_stats();
    ui_update_resource_stats();

    text_printf(&g.info_win, "[%A?%A-Help]", PALETTE_YELLOW, PALETTE_WHITE);

    while (1)
    {
        system_timer_update();

        turn();

        if (g.main_win.dirty == 1)
        {
            map_render();
            g.main_win.dirty = 0;
        }

        if (g.stat_win.dirty == 1)
        {
            ui_update_primary_stats();
            ui_update_secondary_stats();
            ui_update_resource_stats();
            g.stat_win.dirty = 0;
        }

        world_process_entity_destructions();


        #ifndef NDEBUG
        stack = stack_max_usage();
        if (stack > stack_max)
        {
            stack_max = stack;
            text_printf(&g.msg_win, "\nMax stack usage: %u bytes", stack_max);
        }
        #endif
    }
    return 0;
}

/*
 * @brief Entities take there turn
 */
static void turn(void)
{
    entity_id_t id;

    for (uint8_t i = 0; i < g.timer_components.count; i++)
    {
        id = g.timer_components.list[i];

        if (g.timer_components.timers[id].fired == 0)
            continue;

        system_timer_reset(id);

        process_entity_turn(id);
    }
}

static void process_entity_turn(entity_id_t id)
{
    if (entity_has_component(id, COMPONENT_PLAYER))
    {
        if (g.main_win.dirty == 1)
        {
            map_render();
            g.main_win.dirty = 0;
        }
        system_player_update();
    }
    else if (entity_has_component(id, COMPONENT_AI))
    {
        system_ai_process_entity_turn(id);
    }

    if (entity_has_component(id, COMPONENT_ACTIVE_EFFECT))
    {
        system_effect_process_entity_turn(id);
    }
}

static uint16_t stack_max_usage(void)
{
    uint8_t *p = (uint8_t *)STACK_LOW;
    while (*p == STACK_PATTERN && (uintptr_t)p < STACK_HIGH)
        p++;

    return (uint16_t)(STACK_HIGH - (uintptr_t)p);
}


