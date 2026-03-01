/**
 * @file player_actions.c
 * @author Paul Johnson
 * @brief Player world-interaction action implementations
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ecs/systems/PAGE46/player_actions.h"

#include <stdint.h>
#include <stdbool.h>

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE46/target_mode.h"

#include "game/global_state.h"
#include "game/map.h"
#include "game/ui_info.h"

#include "core/util.h"
#include "core/zxnext.h"


/***************************************************
 * private function prototypes
 ***************************************************/
static direction_t dir_or_cancel(void);

/***************************************************
 * public functions
 ***************************************************/
void player_action_climb(void)
{
    entity_id_t e;
    uint8_t x = g.location_components[g.player.id].coord.x;
    uint8_t y = g.location_components[g.player.id].coord.y;

    e = map_get_first(x, y);

    while (e != ENTITY_ID_INVALID)
    {
        if (entity_has_component(e, COMPONENT_TRANSITION))
        {
            system_transition_try(e, g.player.id);
            return;
        }
        e = map_get_next(e);
    }
    text_printf(&g.msg_win, "\nNothing to climb here");
}

void player_action_close(void)
{
    entity_id_t e;
    direction_t dir;
    uint8_t x;
    uint8_t y;

    dir = dir_or_cancel();

    if (dir == DIRECTION_NONE)
        return;

    x = g.location_components[g.player.id].coord.x + directions[dir].x;
    y = g.location_components[g.player.id].coord.y + directions[dir].y;

    e = map_get_first(x, y);

    while (e != ENTITY_ID_INVALID)
    {
        if (entity_has_component(e, COMPONENT_OPENABLE))
        {
            system_door_try_close(g.player.id, e);
            return;
        }
        e = map_get_next(e);
    }
    text_printf(&g.msg_win, "\nNothing to close here");
}

void player_action_melee_attack(void)
{
    entity_id_t e;
    direction_t dir;
    uint8_t x;
    uint8_t y;

    dir = dir_or_cancel();

    if (dir == DIRECTION_NONE)
        return;

    x = g.location_components[g.player.id].coord.x + directions[dir].x;
    y = g.location_components[g.player.id].coord.y + directions[dir].y;

    e = map_get_first(x, y);

    while (e != ENTITY_ID_INVALID)
    {
        if (entity_has_component(e, COMPONENT_DESTRUCTIBLE))
        {
            system_combat_try_attack(g.player.id, e, ATTACK_KIND_MELEE);
            return;
        }
        e = map_get_next(e);
    }
    text_printf(&g.msg_win, "\nNothing to attack here");
}

void player_action_open(void)
{
    entity_id_t e;
    direction_t dir;
    uint8_t x;
    uint8_t y;

    dir = dir_or_cancel();

    if (dir == DIRECTION_NONE)
        return;

    x = g.location_components[g.player.id].coord.x + directions[dir].x;
    y = g.location_components[g.player.id].coord.y + directions[dir].y;

    e = map_get_first(x, y);

    while (e != ENTITY_ID_INVALID)
    {
        if (entity_has_component(e, COMPONENT_OPENABLE))
        {
            system_door_try_open(g.player.id, e);
            return;
        }
        e = map_get_next(e);
    }
    text_printf(&g.msg_win, "\nNothing to open here");
}

void player_action_pickup(void)
{
    entity_id_t e;
    uint8_t x = g.location_components[g.player.id].coord.x;
    uint8_t y = g.location_components[g.player.id].coord.y;

    e = map_get_first(x, y);

    while (e != ENTITY_ID_INVALID)
    {
        if (entity_has_component(e, COMPONENT_STACKABLE))
        {
            system_container_try_pickup(g.player.id, e);
            return;
        }
        e = map_get_next(e);
    }
    text_printf(&g.msg_win, "\nNothing to pick up here");
}

void player_action_target(void)
{
    target_context_t tcx;

    tcx.filter = TARGET_FILTER_ENTITY;
    tcx.max_range = system_combat_attack_range(g.player.id, ATTACK_KIND_RANGED);
    tcx.require_los = true;
    tcx.source.x = g.location_components[g.player.id].coord.x;
    tcx.source.y = g.location_components[g.player.id].coord.y;

    text_printf(&g.msg_win, "\nRange:%d", tcx.max_range);

    ui_info_set_context(UI_CONTEXT_TARGETING);

    target_mode(&tcx);

    if (tcx.target_selected)
    {
        text_print_string(&g.msg_win, "\nRanged attack:");
        system_combat_try_attack(g.player.id, tcx.selected_entity, ATTACK_KIND_RANGED);
    }
}

void player_action_look(void)
{
    target_context_t tcx;

    tcx.filter = TARGET_FILTER_ENTITY;
    tcx.max_range = 255;
    tcx.require_los = false;
    tcx.source.x = g.location_components[g.player.id].coord.x;
    tcx.source.y = g.location_components[g.player.id].coord.y;

    ui_info_set_context(UI_CONTEXT_LOOK);

    target_mode(&tcx);

    if (tcx.target_selected)
    {
        text_print_string(&g.msg_win, "\nSee:");
        system_name_print(&g.msg_win, g.name_components[tcx.selected_entity]);
    }
}

/***************************************************
 * private functions
 ***************************************************/
static direction_t dir_or_cancel(void)
{
    unsigned int key;

    ui_info_set_context(UI_CONTEXT_DIRECTION);

    key = key_press();

    switch (key)
    {
    case KEY_DOWN:
        return DIRECTION_SOUTH;

    case KEY_UP:
        return DIRECTION_NORTH;

    case KEY_LEFT:
        return DIRECTION_WEST;

    case KEY_RIGHT:
        return DIRECTION_EAST;

    default:
        return DIRECTION_NONE;
    }
}
