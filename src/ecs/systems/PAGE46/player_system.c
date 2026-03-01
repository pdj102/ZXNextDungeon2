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
#include "game/camera.h"
#include "game/ui_info.h"

#include "core/util.h"
#include "core/zxnext.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void climb(void);
static void close(void);
static void drop(void);
static void eat(void);
static void equip(void);
static void inventory(void);
static void look(void);
static void open(void);
static void melee_attack(void);
static void pickup(void);
static void target(void);
static void unequip(void);
static void killed_something(const event_t *event);

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
            killed_something(event);
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

    /* Check player is not dead */
    if (g.creature_components[entity].status == CREATURE_STATUS_DEAD)
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
            climb();
            break;
        case KEY_GREATERTHAN: /* '>' down */
            climb();
            break;            
        case KEY_U_E: /* 'E' eat */
            eat();
            break;                     
        case KEY_L_A: /* 'a' melee attack */
            melee_attack();
            break;
        case KEY_L_C: /* 'c' close */
            close();
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
        case KEY_L_O: /* 'o' open */
            open();
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
static void climb(void)
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

 static void close(void)
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

static void melee_attack(void)
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

static void drop(void)
{
    entity_id_t e = prompt_inventory_item("Select item to drop");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_container_try_drop(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot drop that");
    }
}

static void eat(void)
{
    entity_id_t e = prompt_inventory_item("Select item to eat");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_consumable_try_consume(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot eat that");
    }
}

static void open(void)
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

static void pickup(void)
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

static void target(void)
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

static void look(void)
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

static void inventory(void)
{
    int key;

    text_cls(&g.main_win);
    text_printf(&g.main_win, "Inventory\n");
    display_inventory();
    text_print_string(&g.main_win, "\nPress any key to continue...");

    key = key_press();
}

void equip(void)
{
    entity_id_t e = prompt_inventory_item("Select item to equip");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_equip(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot equip that");
    } 
}

static void unequip(void)
{
    entity_id_t e = prompt_inventory_item("Select item to unequip");
    if (e == ENTITY_ID_INVALID)
        return;

    if (!system_equipment_try_unequip(g.player.id, e))
    {
        text_printf(&g.msg_win, "\nYou cannot unequip that");
    }
}

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
#define PLAYER_MAX_LEVEL 10

static void killed_something(const event_t *event)
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
        g.player.level++;
        text_printf(&g.msg_win, "\nLevel up! You are now level %d.", (uint16_t)g.player.level);
    }

    g.stat_win.dirty = 1;
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

    text_print_string(&g.main_win, "\n");

    while (item != ENTITY_ID_INVALID)
    {
        text_printf(&g.main_win, "(%c) ", c);
        if (entity_has_component(item, COMPONENT_STACKABLE))
        {
            text_printf(&g.main_win, "%d ", g.stackable_components[item].quantity);
        }
        else
        {
            text_print_string(&g.main_win, "a ");
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

static direction_t dir_or_cancel( void )
{
    unsigned int key;

    ui_info_set_context(UI_CONTEXT_DIRECTION);

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