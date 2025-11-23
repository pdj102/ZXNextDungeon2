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

#include "../../entity.h"
#include "../../components/timer_comp.h"
#include "../../components/location_comp.h"

#include "../../../core/systems_dispatch.h"

#include "../../../game/global_state.h"
#include "../../../game/map.h"

#include "../../../core/util.h"
#include "../../../core/zxnext.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
void melee_attack(void);
void pickup(void);
void drop(void);
void inventory(void);
void display_inventory(void);
uint8_t prompt_letter(uint8_t max_index);
bool_t is_equipped(entity_id_t entity);


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

    util_assert(entity != ENTITY_ID_INVALID);
    util_assert(entity_has_component(entity, COMPONENT_PLAYER_CTRL));
    util_assert(entity_has_flag(entity, FLAG_IN_USE));  /* Player entity has not been destroyed */

    /* Check if player's turn*/
    if (timer_has_fired(entity) == 0)
    {
        return;
    }

    /* Reset timer */
    timer_reset(entity);

    key = key_press();

    text_printf(&g.msg_win, "key: %d\n", key);

    switch(key) {
        case 8: /* left */
            system_actions_try_move(entity, -1, 0);
            break;
        case 9: /* right */
            system_actions_try_move(entity, 1, 0);
            break;
        case 11: /* up */
            system_actions_try_move(entity, 0, -1);
            break;
        case 10: /* down */
            system_actions_try_move(entity, 0, 1);
            break;
        case 56: /* camera right */
            g.map.camera.x++;
            break;            
        case 97: /* melee attack */
            melee_attack();
            break;            
        case 100: /* drop an item */
            drop();
            break;
        case 103: /* get object from floor */
            pickup();
            break;
        case 105: /* view inventory */
            inventory();
            break;                      
        default:
            break;
    }
}

 /***************************************************
 * private functions
 ***************************************************/

void melee_attack(void)
{
    entity_id_t target;
    direction_t dir;
    uint8_t x;
    uint8_t y;

    dir = util_get_dir_or_cancel_b();

    x = g.location_components[g.player.id].x + directions[dir].x;
    y = g.location_components[g.player.id].y + directions[dir].y;

    target = g.map.cell_head[x][y];

    while (target != ENTITY_ID_INVALID)
    {
        if (entity_has_component(target, COMPONENT_CREATURE))
        {
            system_actions_try_melee_attack(g.player.id, target);
            return;
        }
        target = g.location_components[target].next_in_location;
    }
    text_printf(&g.msg_win, "Nothing to attack here\n");
}    

 void drop(void)
{
    entity_id_t item;
    uint8_t index;
    uint8_t count;

    count = system_container_count(g.player.id);

    if (count == 0)
    {
        text_printf(&g.msg_win, "Nothing to drop\n");
        return;
    }

    display_inventory();

    index = prompt_letter(count - 1);

    if (index == 99)
    {
        return;
    }
   
    item = system_container_get_at(g.player.id, index);
    system_actions_try_drop(g.player.id, item);
}

void pickup(void)
{
    entity_id_t item;
    uint8_t x = g.location_components[g.player.id].x;
    uint8_t y = g.location_components[g.player.id].y;

    item = g.map.cell_head[x][y];

    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_component(item, COMPONENT_ITEM))
        {
            system_actions_try_pickup(g.player.id, item);
            return;
        }
        item = g.location_components[item].next_in_location;
    }
    text_printf(&g.msg_win, "Nothing to pick up here\n");
}

void inventory(void)
{
    int key;

    display_inventory();

    text_print_string(&g.main_win, "Press any key to continue...\n");

    key = key_press();
}

void display_inventory(void)
{
    entity_id_t entity;
    unsigned char c = 'a';

    text_cls(&g.main_win);
    text_print_string(&g.main_win, "Inventory\n");

    entity = system_container_get_first(g.player.id);

    while (entity != ENTITY_ID_INVALID)
    {
        text_printf(&g.main_win, "(%c) ", c);
        item_print_name(&g.main_win, entity);
        if (is_equipped(entity))
        {
        text_print_string(&g.main_win, "(equipped)");    
        }
        text_print_string(&g.main_win, "\n");

        c++;
        entity = system_container_get_next(entity);
    }
}

/*
 * @brief Prompt the user for a letter within a specified range. 
 * @param max_index The maximum index of the letter range .e.g. 0 -> only 'a', 1 -> 'a'..'b', 5 -> 'a'..'f'
 * @return The selected letter as an integer, 'a' -> 0, 'b' -> 1 etc, or 99 for cancel.
 */
uint8_t prompt_letter(uint8_t max_index)
{
    uint8_t max_char = 'a' + max_index;

    text_printf(&g.msg_win, "[a-%c] (or any other key to cancel)\n", max_char);

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

bool_t is_equipped(entity_id_t entity)
{
    if (g.player.head == entity ||
        g.player.neck == entity || 
        g.player.body == entity ||
        g.player.hands == entity ||
        g.player.left_finger == entity ||
        g.player.right_finger == entity ||
        g.player.legs == entity ||
        g.player.feet == entity ||
        g.player.melee_weapon == entity ||
        g.player.ranged_weapon == entity ||
        g.player.quiver == entity)
        {
            return 1;
        }
        
    return 0;       
}