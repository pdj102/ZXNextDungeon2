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

#include <sys\types.h>

#include "global_state.h"
#include "entity.h"
#include "location_comp.h"

#include "movement_system.h"

#include "creature_actions.h"

#include "map.h"
#include "util.h"

#include "zxnext.h"


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

    if ( (entity == ENTITY_ID_INVALID) || (!entity_has_component(entity, COMPONENT_PLAYER_CTRL) ))
    {
        return; /* no player */
    }

    /* TODO checking if creature component is alive */

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
        case 100: /* drop an item */
            drop();
            break;
        case 103: /* get object from floor */
            pickup();
            break;            
        default:
            break;
    }
}

 /***************************************************
 * private functions
 ***************************************************/

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
            if (creature_actions_try_pickup(g.player.id, item))
            {
                text_printf(&g.msg_win, "Picked up %u\n", item);
                text_printf(&g.msg_win, "Player container head %u\n", g.container_components[g.player.id].head);
                return;
            }
        }
        item = g.location_components[item].next_in_location;
    }
    text_printf(&g.msg_win, "Nothing to pick up here\n");
}

void drop(void)
{
   entity_id_t item;
   
   item = g.container_components[g.player.id].head;

   if (item == ENTITY_ID_INVALID)
   {
        text_printf(&g.msg_win, "Nothing to drop\n");
        return;
   }

   creature_actions_try_drop(g.player.id, item);
}