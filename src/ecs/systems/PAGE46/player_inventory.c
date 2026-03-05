/**
 * @file player_inventory.c
 * @author Paul Johnson
 * @brief Player inventory management actions
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ecs/systems/PAGE46/player_inventory.h"

#include <stdint.h>
#include <stdbool.h>

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"
#include "game/ui_info.h"

#include "core/util.h"
#include "core/zxnext.h"


/***************************************************
 * private function prototypes
 ***************************************************/
static void display_inventory(void);
static entity_id_t prompt_inventory_item(const char *prompt_msg);
static entity_id_t prompt_consumable_by_method(const char *prompt_msg, consume_method_t method);
static uint8_t prompt_letter(uint8_t max_index);

/***************************************************
 * public functions
 ***************************************************/
void player_inventory_show(void)
{
    int key;

    text_cls(&g.main_win);
    text_printf(&g.main_win, "Inventory\n");
    display_inventory();
    text_print_string(&g.main_win, "\nPress any key to continue...");

    key = key_press();

    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}

void player_inventory_drop(void)
{
    entity_id_t e = prompt_inventory_item("Select item to drop");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_container_try_drop(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot drop that");
    }
    
    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}

void player_inventory_eat(void)
{
    entity_id_t e = prompt_consumable_by_method("Select food to eat", CONSUME_METHOD_EAT);
    if (e == ENTITY_ID_INVALID)
        return;

    if (system_consumable_try_consume(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou eat the ");
        system_name_print(&g.msg_win, g.name_components[e]);
        text_print_string(&g.msg_win, ".");
    }
    else
    {
        text_printf(&g.msg_win, "\nYou cannot eat that");
    }
    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}

void player_inventory_equip(void)
{
    entity_id_t e = prompt_inventory_item("Select item to equip");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_equip(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot equip that");
    }
    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}

void player_inventory_unequip(void)
{
    entity_id_t e = prompt_inventory_item("Select item to unequip");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_unequip(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot unequip that");
    }
    g.map_win.dirty = 1;
    g.info_win.dirty = 1;
}

/***************************************************
 * private functions
 ***************************************************/
static void display_inventory(void)
{
    entity_id_t item;
    unsigned char c = 'a';

    item = system_container_get_first(g.player.id);

    text_print_string(&g.main_win, "\n");

    while (item != ENTITY_ID_INVALID)
    {
        text_printf(&g.main_win, "(%c) ", c);
        if (entity_has_component(item, COMPONENT_STACKABLE))
        {
            text_printf(&g.main_win, "%d ", g.stackable_components[item].quantity);
        }

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

static entity_id_t prompt_consumable_by_method(const char *prompt_msg, consume_method_t method)
{
    entity_id_t item;
    uint8_t count = 0;
    uint8_t index;
    uint8_t n;
    unsigned char c;

    /* Count matching items */
    item = system_container_get_first(g.player.id);
    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_component(item, COMPONENT_CONSUMABLE) &&
            g.consumable_components[item].method == method)
            count++;
        item = system_container_get_next(item);
    }

    if (count == 0)
    {
        text_printf(&g.msg_win, "\nNothing to eat");
        return ENTITY_ID_INVALID;
    }

    /* Display matching items */
    text_cls(&g.main_win);
    text_printf(&g.main_win, "%s\n\n", prompt_msg);
    c = 'a';
    item = system_container_get_first(g.player.id);
    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_component(item, COMPONENT_CONSUMABLE) &&
            g.consumable_components[item].method == method)
        {
            text_printf(&g.main_win, "(%c) ", c);
            if (entity_has_component(item, COMPONENT_STACKABLE))
                text_printf(&g.main_win, "%d ", g.stackable_components[item].quantity);
            system_name_print(&g.main_win, g.name_components[item]);
            text_print_string(&g.main_win, "\n");
            c++;
        }
        item = system_container_get_next(item);
    }
    g.main_win.dirty = 1;

    index = prompt_letter(count - 1);
    if (index == 99)
        return ENTITY_ID_INVALID;

    /* Return the Nth matching item */
    n = 0;
    item = system_container_get_first(g.player.id);
    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_component(item, COMPONENT_CONSUMABLE) &&
            g.consumable_components[item].method == method)
        {
            if (n == index)
                return item;
            n++;
        }
        item = system_container_get_next(item);
    }
    return ENTITY_ID_INVALID;
}

/*
 * @brief Prompt the user for a letter within a specified range.
 * @param max_index The maximum index of the letter range .e.g. 0 -> only 'a', 1 -> 'a'..'b', 5 -> 'a'..'f'
 * @return The selected letter as an integer, 'a' -> 0, 'b' -> 1 etc, or 99 for cancel.
 */
static uint8_t prompt_letter(uint8_t max_index)
{
    uint8_t max_char = 'a' + max_index;

    ui_info_set_inventory_context(max_char);

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
