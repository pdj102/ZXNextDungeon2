/**
 * @file player_system.c
 * @author Paul Johnson
 * @brief

 *
 * @copyright Copyright (c) 2025
 *
 */

#include "player_system.h"

#include <stdint.h>
#include <stdbool.h>      /* bool */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE46/player_actions.h"
#include "ecs/systems/PAGE46/player_inventory.h"
#include "ecs/systems/PAGE46/player_progression.h"

#include "game/global_state.h"
#include "game/camera.h"
#include "game/ui_info.h"

#include "core/util.h"
#include "core/zxnext.h"


 /***************************************************
 * public functions
 ***************************************************/

void player_system_handle_event(const event_t *event)
{
    if (entity_has_component(event->source, COMPONENT_PLAYER))
    {
        // Player is the source - Player did something
        switch (event->type)
        {
        case EVENT_SPOTTED_TARGET:
            util_info("PLayer event saw entity");
            break;
        case EVENT_KILLED:
            // Player killed something, check if it was the current target and if so, give up target (switch to idle)
            player_progression_on_kill(event);
            break;
        }
    }
    else if (entity_has_component(event->target, COMPONENT_PLAYER))
    {
        // Player is the target - something happened to the Player
        switch (event->type)
        {
            case EVENT_KILLED:
                // Player was killed, set player entity to invalid
                // g.player.id = ENTITY_ID_INVALID;
                g.creature_components[event->target].status = CREATURE_STATUS_DEAD;
            break;
        }
    }
}

void player_system_update(void)
{
    uint8_t entity = g.player.id;
    int key;

    if (entity == ENTITY_ID_INVALID)
    {
        return;
    }

    util_assert(entity != ENTITY_ID_INVALID);
    util_assert(entity_has_component(entity, COMPONENT_PLAYER));
    util_assert(entity_has_component(entity, COMPONENT_CREATURE));
    util_assert(entity_has_component(entity, COMPONENT_TIMER));
    util_assert(entity_has_flag(entity, FLAG_IN_USE));  /* Player entity has not been destroyed */

    /* Check player is not dead or has won */
    if (g.creature_components[entity].status == CREATURE_STATUS_DEAD ||
        g.creature_components[entity].status == CREATURE_STATUS_WON)
    {
        return;
    }

    ui_info_set_context(UI_CONTEXT_NORMAL);

    key = key_press();

    text_printf(&g.msg_win, "\nkey: %d", key);

    switch(key) {
        case KEY_LEFT: /* left */
            system_movement_try_move(entity, -1, 0);
            camera_update();
            break;
        case KEY_RIGHT: /* right */
            system_movement_try_move(entity, 1, 0);
            camera_update();
            break;
        case KEY_UP: /* up */
            system_movement_try_move(entity, 0, -1);
            camera_update();
            break;
        case KEY_DOWN: /* down */
            system_movement_try_move(entity, 0, 1);
            camera_update();
            break;
        case KEY_LESSTHAN: /* '<' down */
            player_action_climb();
            break;
        case KEY_GREATERTHAN: /* '>' down */
            player_action_climb();
            break;
        case KEY_U_E: /* 'E' eat */
            player_inventory_eat();
            break;
        case KEY_L_A: /* 'a' melee attack */
            player_action_melee_attack();
            break;
        case KEY_L_C: /* 'c' close */
            player_action_close();
            break;
        case KEY_L_D: /* 'd' drop an item */
            player_inventory_drop();
            break;
        case KEY_L_E: /* 'e' equip an item */
            player_inventory_equip();
            break;
        case KEY_L_G: /* 'g' get object from floor */
            player_action_pickup();
            break;
        case KEY_L_I: /* 'i' view inventory */
            player_inventory_show();
            break;
        case KEY_L_L: /* 'l' look around */
            player_action_look();
            break;
        case KEY_L_O: /* 'o' open */
            player_action_open();
            break;
        case KEY_L_T: /* 't' target (ranged attack) */
            player_action_target();
            break;
        case KEY_L_U: /* 'u' unequip an item */
            player_inventory_unequip();
            break;
        default:
            break;
    }
}

