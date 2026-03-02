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
#include "game/camera.h"
#include "game/global_state.h"
#include "game/world.h"
#include "game/PAGE34/dungeon_gen.h"
#include "game/ui_info.h"

#include "core/util.h"

#define STACK_HIGH 0xbfff
#define STACK_LOW (STACK_HIGH - 0x10E)
#define STACK_PATTERN 0xCD

static uint16_t stack_max_usage(void);
static void turn(void);
static void process_entity_turn(entity_id_t id);

int main(void)
{
    static uint16_t stack_max = 0;
    static uint16_t stack = 0;
    static uint8_t *p = (uint8_t *)STACK_LOW; 

    zxnext_init();        

    ui_init();
    
    util_info("Debug build");
    text_printf(&g.msg_win, "\nGlobal size:%U", sizeof(g));
    util_assert(sizeof(g) < 0x3FFF);

    new_game();

    camera_update();

    ui_update();

    ui_info_set_context(UI_CONTEXT_NORMAL);

    /* ===== Init Stack Guard NB this will corrupt the main stack frame ==== */
    while ((uintptr_t)p < STACK_HIGH)
        *p++ = STACK_PATTERN;    
  

    while (1)
    {
        system_timer_update();

        turn();

        ui_update();

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
        system_event_process_queue();
    }
}

static void process_entity_turn(entity_id_t id)
{
    if (entity_has_component(id, COMPONENT_PLAYER))
    {
        /* if (g.map_win.dirty == 1)
        {
            map_render();
            g.map_win.dirty = 0;
        }
        */
       ui_update();
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


