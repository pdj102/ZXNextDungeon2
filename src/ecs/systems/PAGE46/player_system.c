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
#include <sys\types.h>      /* bool_t */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

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
static void melee_attack(void);
static void drop(void);
static void eat(void);
static void equip(void);
static void inventory(void);
static void pickup(void);
static void unequip(void);

static void display_inventory(void);
static entity_id_t prompt_inventory_item(const char *prompt_msg);
static uint8_t prompt_letter(uint8_t max_index);

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
    if (g.creature_components[entity].status != CREATURE_STATUS_ALIVE)
    {
        return;
    }

    /* Check if player's turn*/
    if (system_timer_has_fired(entity) == 0)
    {
        return;
    }

    /* Reset timer */
    system_timer_reset(entity);

    key = key_press();

    text_printf(&g.msg_win, "key: %d\n", key);

    switch(key) {
        case 8: /* left */
            system_movement_try_move(entity, -1, 0);
            break;
        case 9: /* right */
            system_movement_try_move(entity, 1, 0);
            break;
        case 11: /* up */
            system_movement_try_move(entity, 0, -1);
            break;
        case 10: /* down */
            system_movement_try_move(entity, 0, 1);
            break;
        case 56: /* '8' camera right */
            g.map.camera.x++;
            break;
        case 69: /* 'E' eat */
            eat();
            break;                        
        case 97: /* 'a' melee attack */
            melee_attack();
            break;            
        case 100: /* 'd' drop an item */
            drop();
            break;
        case 101: /* 'e' equip an item */
            equip();            
            break;
        case 103: /* 'g' get object from floor */
            pickup();
            break;
        case 105: /* 'i' view inventory */
            inventory();
            break;
        case 117: /* 'u' unequip an item */
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

    dir = game_get_dir_or_cancel_b();

    x = g.location_components[g.player.id].x + directions[dir].x;
    y = g.location_components[g.player.id].y + directions[dir].y;

    target = g.map.cell_head[x][y];

    while (target != ENTITY_ID_INVALID)
    {
        if (entity_has_component(target, COMPONENT_DESTRUCTIBLE))
        {
            system_combat_try_melee_attack(g.player.id, target);
            return;
        }
        target = g.location_components[target].next_in_location;
    }
    text_printf(&g.msg_win, "Nothing to attack here\n");
}

static void drop(void)
{
    entity_id_t item = prompt_inventory_item("Select item to drop");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_container_try_drop(g.player.id, item))
    {
        text_printf(&g.msg_win, "You cannot drop that\n");
    }
}

static void eat(void)
{
    entity_id_t item = prompt_inventory_item("Select item to eat");
    if (item == ENTITY_ID_INVALID)
        return;

    if (!system_consumable_try_consume(g.player.id, item))
    {
        text_printf(&g.msg_win, "You cannot eat that\n");
    }
}

static void pickup(void)
{
    entity_id_t item;
    uint8_t x = g.location_components[g.player.id].x;
    uint8_t y = g.location_components[g.player.id].y;

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
    text_printf(&g.msg_win, "Nothing to pick up here\n");
}

static void inventory(void)
{
    int key;

    text_cls(&g.main_win);
    text_printf(&g.main_win, "Inventory\n");
    display_inventory();
    text_print_string(&g.main_win, "Press any key to continue...\n");

    key = key_press();
}

void equip(void)
{
    entity_id_t item;
    uint8_t index;
    uint8_t count;

    count = system_container_count(g.player.id);

    if (count == 0)
    {
        text_printf(&g.msg_win, "Nothing in inventory\n");
        return;
    }

    display_inventory();

    index = prompt_letter(count - 1);

    if (index == 99)
    {
        return;
    }
   
    item = system_container_get_at(g.player.id, index);
    system_equipment_try_equip(g.player.id, item);    
}

static void unequip(void)
{
    entity_id_t item;
    uint8_t index;
    uint8_t count;

    count = system_container_count(g.player.id);

    if (count == 0)
    {
        text_printf(&g.msg_win, "Nothing in inventory\n");
        return;
    }

    display_inventory();

    index = prompt_letter(count - 1);

    if (index == 99)
    {
        return;
    }
   
    item = system_container_get_at(g.player.id, index);
    system_equipment_try_unequip(g.player.id, item);
}

static entity_id_t prompt_inventory_item(const char *prompt_msg)
{
    uint8_t count;
    uint8_t index;

    count = system_container_count(g.player.id);
    if (count == 0)
    {
        text_printf(&g.msg_win, "%s\n", "Inventory is empty\n");
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
}

/*
 * @brief Prompt the user for a letter within a specified range. 
 * @param max_index The maximum index of the letter range .e.g. 0 -> only 'a', 1 -> 'a'..'b', 5 -> 'a'..'f'
 * @return The selected letter as an integer, 'a' -> 0, 'b' -> 1 etc, or 99 for cancel.
 */
static uint8_t prompt_letter(uint8_t max_index)
{
    uint8_t max_char = 'a' + max_index;

    text_printf(&g.main_win, "Select a letter [a-%c] (or any other key to cancel)\n", max_char);

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