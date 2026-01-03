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
#include "ecs/systems/PAGE46/target_mode.h"

#include "game/global_state.h"
#include "game/map.h"

#include "core/util.h"
#include "core/zxnext.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void drop(void);
static void eat(void);
static void equip(void);
static void inventory(void);
static void look(void);
static void melee_attack(void);
static void pickup(void);
static void target(void);
static void unequip(void);

static void display_inventory(void);
static entity_id_t prompt_inventory_item(const char *prompt_msg);
static uint8_t prompt_letter(uint8_t max_index);
static direction_t dir_or_cancel( void );

 /***************************************************
 * public functions
 ***************************************************/
void player_system_init(void)
{
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

    /* Check player is not dead */
    if (g.creature_components[entity].status == CREATURE_STATUS_DEAD)
    {
        return;
    }

    key = key_press();

    text_printf(&g.msg_win, "\nkey: %d", key);

    switch(key) {
        case KEY_LEFT: /* left */
            system_movement_try_move(entity, -1, 0);
            break;
        case KEY_RIGHT: /* right */
            system_movement_try_move(entity, 1, 0);
            break;
        case KEY_UP: /* up */
            system_movement_try_move(entity, 0, -1);
            break;
        case KEY_DOWN: /* down */
            system_movement_try_move(entity, 0, 1);
            break;
        case 56: /* '8' camera right */
            g.camera.x++;
            break;
        case KEY_U_E: /* 'E' eat */
            eat();
            break;                        
        case KEY_L_A: /* 'a' melee attack */
            melee_attack();
            break;            
        case KEY_L_D: /* 'd' drop an item */
            drop();
            break;
        case KEY_L_E: /* 'e' equip an item */
            equip();            
            break;
        case KEY_L_G: /* 'g' get object from floor */
            pickup();
            break;
        case KEY_L_I: /* 'i' view inventory */
            inventory();
            break;
        case KEY_L_L: /* 'l' look around */
            look();
            break;            
        case KEY_L_T: /* 't' target (ranged attack) */
            target();
            break;            
        case KEY_L_U: /* 'u' unequip an item */
            unequip();
            break;
        default:
            break;
    }
}

 /***************************************************
 * private functions
 ***************************************************/

static void melee_attack(void)
{
    entity_id_t target;
    direction_t dir;
    uint8_t x;
    uint8_t y;

    dir = dir_or_cancel();

    if (dir == DIRECTION_NONE)
        return;

    x = g.location_components[g.player.id].coord.x + directions[dir].x;
    y = g.location_components[g.player.id].coord.y + directions[dir].y;

    target = g.map.cell_head[x][y];

    while (target != ENTITY_ID_INVALID)
    {
        if (entity_has_component(target, COMPONENT_DESTRUCTIBLE))
        {
            system_combat_try_attack(g.player.id, target, ATTACK_KIND_MELEE);
            return;
        }
        target = g.location_components[target].next_in_location;
    }
    text_printf(&g.msg_win, "\nNothing to attack here");
}

static void drop(void)
{
    entity_id_t item = prompt_inventory_item("Select item to drop");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_container_try_drop(g.player.id, item))
    {
        text_printf(&g.msg_win, "\nYou cannot drop that");
    }
}

static void eat(void)
{
    entity_id_t item = prompt_inventory_item("Select item to eat");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_consumable_try_consume(g.player.id, item))
    {
        text_printf(&g.msg_win, "\nYou cannot eat that");
    }
}

static void pickup(void)
{
    entity_id_t item;
    uint8_t x = g.location_components[g.player.id].coord.x;
    uint8_t y = g.location_components[g.player.id].coord.y;

    item = g.map.cell_head[x][y];

    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_component(item, COMPONENT_ITEM))
        {
            system_container_try_pickup(g.player.id, item);
            return;
        }
        item = g.location_components[item].next_in_location;
    }
    text_printf(&g.msg_win, "\nNothing to pick up here");
}

static void target(void)
{
    target_context_t tcx;

    tcx.filter = TARGET_FILTER_ENTITY;
    tcx.max_range = system_combat_attack_range(g.player.id, ATTACK_KIND_RANGED);
    tcx.require_los = true;
    tcx.source.x = g.location_components[g.player.id].coord.x;
    tcx.source.y = g.location_components[g.player.id].coord.y;

    text_printf(&g.msg_win, "\nRange:%d", tcx.max_range);

    text_printf(&g.info_win, "\n[%PYcursor%PW-dir] [%PYt%PW-attack] [%PYspace%PW-cancel]");

    target_mode(&tcx);

    if (tcx.target_selected)
    {
        text_print_string(&g.msg_win, "\nRanged attack:");
        system_combat_try_attack(g.player.id, tcx.selected_entity, ATTACK_KIND_RANGED);
    }
}

static void look(void)
{
    target_context_t tcx;

    tcx.filter = TARGET_FILTER_ENTITY;
    tcx.max_range = 255;
    tcx.require_los = false;
    tcx.source.x = g.location_components[g.player.id].coord.x;
    tcx.source.y = g.location_components[g.player.id].coord.y;

    text_printf(&g.info_win, "\n[%PYcursor%PW-dir] [%PYl%PW-look] [%PYspace%PW-cancel]");
    
    target_mode(&tcx);

    if (tcx.target_selected)
    {
        text_print_string(&g.msg_win, "\nSee:");
        system_name_print(&g.msg_win, g.name_components[tcx.selected_entity]);
    }
}

static void inventory(void)
{
    int key;

    text_cls(&g.main_win);
    text_printf(&g.main_win, "\nInventory");
    display_inventory();
    text_print_string(&g.main_win, "\nPress any key to continue...");

    key = key_press();
}

void equip(void)
{
    entity_id_t item = prompt_inventory_item("Select item to equip");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_equip(g.player.id, item))
    {
        text_printf(&g.msg_win, "\nYou cannot equip that");
    } 
}

static void unequip(void)
{
    entity_id_t item = prompt_inventory_item("Select item to unequip");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_unequip(g.player.id, item))
    {
        text_printf(&g.msg_win, "\nYou cannot unequip that");
    }
}

static entity_id_t prompt_inventory_item(const char *prompt_msg)
{
    uint8_t count;
    uint8_t index;

    count = system_container_count(g.player.id);
    if (count == 0)
    {
        text_printf(&g.msg_win, "\nInventory is empty");
        return ENTITY_ID_INVALID;
    }

    text_cls(&g.main_win);
    text_printf(&g.main_win, "%s\n", prompt_msg);

    display_inventory();

    index = prompt_letter(count - 1);
    if (index == 99)
        return ENTITY_ID_INVALID;

    return system_container_get_at(g.player.id, index);
}


static void display_inventory(void)
{
    entity_id_t item;
    unsigned char c = 'a';

    item = system_container_get_first(g.player.id);

    while (item != ENTITY_ID_INVALID)
    {
        text_printf(&g.main_win, "(%c) ", c);
        system_name_print(&g.main_win, g.name_components[item]);

        if (system_equipment_is_equipped(g.player.id, item))
        {
        text_print_string(&g.main_win, " (equipped)");    
        }
        text_print_string(&g.main_win, "\n");

        c++;
        item = system_container_get_next(item);
    }
    g.main_win.dirty = 1;
}

/*
 * @brief Prompt the user for a letter within a specified range. 
 * @param max_index The maximum index of the letter range .e.g. 0 -> only 'a', 1 -> 'a'..'b', 5 -> 'a'..'f'
 * @return The selected letter as an integer, 'a' -> 0, 'b' -> 1 etc, or 99 for cancel.
 */
static uint8_t prompt_letter(uint8_t max_index)
{
    uint8_t max_char = 'a' + max_index;

    text_printf(&g.info_win, "\n[%PYa-%c%PW-select] [%PYspace%PW-cancel]", max_char);

    /* Get a single character */
    int ch = key_press();

    /* Convert to lowercase if needed */
    if (ch >= 'A' && ch <= 'Z')
        ch = ch - 'A' + 'a';

    /* Validate range */
    if (ch < 'a' || ch > max_char)
        return 99;            /* Cancel */

    return (uint8_t)(ch - 'a');
}

static direction_t dir_or_cancel( void )
{
    unsigned int key;

    text_printf(&g.info_win, "\n[%ACursor keys%A-direction] [%ASpace%A-cancel]", PALETTE_YELLOW, PALETTE_WHITE, PALETTE_YELLOW, PALETTE_WHITE);

    key = key_press();   

    switch (key)
    {

    case KEY_DOWN: // down
        return DIRECTION_SOUTH;

    case KEY_UP: // up
        return DIRECTION_NORTH;

    case KEY_LEFT: // left
        return DIRECTION_WEST;

    case KEY_RIGHT: // right
        return DIRECTION_EAST;

    default:
        return DIRECTION_NONE;
    }
}