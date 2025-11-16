/**
 * @file player_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "player_system.h"

#include "player_system_priv.h"

#include <sys\types.h>      /* bool_t */

#include "../entity.h"
#include "../components/timer_comp.h"
#include "../components/location_comp.h"
#include "movement_system.h"
#include "actions_system.h"
#include "container_system.h"

#include "../../game/global_state.h"
#include "../../game/map.h"

#include "../../core/util.h"
#include "../../core/zxnext.h"


/***************************************************
 * private variables
 * ***************************************************/



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
    if (timer_fired(entity) == 0)
    {
        return;
    }

    /* Reset timer */
    timer_reset(entity);

    key = key_press();

    text_printf(&g.msg_win, "key: %d\n", key);

    switch(key) {
        case 8: /* left */
            movement_system_try_move(entity, -1, 0);
            break;
        case 9: /* right */
            movement_system_try_move(entity, 1, 0);
            break;
        case 11: /* up */
            movement_system_try_move(entity, 0, -1);
            break;
        case 10: /* down */
            movement_system_try_move(entity, 0, 1);
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
            actions_system_try_melee_attack(g.player.id, target);
            return;
        }
        target = g.location_components[target].next_in_location;
    }
    text_printf(&g.msg_win, "Nothing to attack here\n");
}    

 void drop(void)
{
    entity_id_t item;
    int key;
    uint8_t count;

    count = container_count(g.player.id);

    if (count == 0)
    {
        text_printf(&g.msg_win, "Nothing to drop\n");
        return;
    }

    display_inventory();

    prompt_letter(count - 1);
   
    // actions_system_try_drop(g.player.id, item);
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
            actions_system_try_pickup(g.player.id, item);
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

    entity = container_get_first(g.player.id);

    while (entity != ENTITY_ID_INVALID)
    {
        text_printf(&g.main_win, "(%c) ", c);
        item_print_name(&g.main_win, entity);
        text_print_string(&g.main_win, "\n");

        c++;
        entity = container_get_next(entity);
    }
}

#include <stdint.h>

int8_t prompt_letter(uint8_t max_index)
{
    /* max_index = highest allowed letter index
       e.g. 0 -> only 'a'
            1 -> 'a'..'b'
            5 -> 'a'..'f'
    */

    uint8_t max_char = 'a' + max_index;

    // text_printf(&g.msg_win, "Press a letter between 'a' and '%c' (or any other key to cancel)\n", max_char);
     text_printf(&g.msg_win, "'%d'\n", max_char);

    /* Get a single character */
    int ch = key_press();

    /* Convert to lowercase if needed */
    if (ch >= 'A' && ch <= 'Z')
        ch = ch - 'A' + 'a';

    /* Validate range */
    if (ch < 'a' || ch > max_char)
        return -1;            /* Cancel */

    return (int8_t)(ch - 'a');
}
