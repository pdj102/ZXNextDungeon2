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

#include "entity.h"
#include "item_comp.h"
#include "creature_comp.h"
#include "location_comp.h"

#include "entity_factory.h"

#include "player_system.h"

#include "map_terrain.h"
#include "map_render.h"

#include "global_state.h"

#include "util.h"
#include "text.h"

#include "PAGE0/init.h"

#include "PAGE30/creature_base.h"


 
int main(void) {

   init_zxnext();
   init_game_state();
   init_ui();


   text_printf(&g.msg_win, "Global size:%U\n", sizeof(g));

    // Create some items
    entity_id_t e1 = entity_factory_create_item(ITEM_SWORD, 1);
    location_add(e1, 10, 10);
    // text_printf(&g.msg_win, "Item Entity ID: %u\n", e1);

    entity_id_t e2 = entity_factory_create_item(ITEM_POTION, 1);
    location_add(e2, 12, 10);
    // text_printf(&g.msg_win, "Item Entity ID: %u\n", e2);

    entity_id_t e3 = entity_factory_create_item(ITEM_KEY, 1);
    // text_printf(&g.msg_win, "Item Entity ID: %u\n", e3);    
    location_add(e3, 14, 10);

    entity_id_t e4 = entity_factory_create_monster(CREATURE_RAT);
    // text_printf(&g.msg_win, "Item Entity ID: %u\n", e4);    
    location_add(e4, 10, 12);

    entity_id_t e5 = entity_factory_create_player();
    // text_printf(&g.msg_win, "Item Entity ID: %u\n", e5);    
    location_add(e5, 10, 15);

    map_render();

    while(1)
    {
        // Main loop code here
        /* energy system */
        /* player control system*/
        // player_control_system_run();
        map_render();

        text_cls(&g.stat_win);
        text_printf(&g.stat_win, "hp:%u\n", g.creature_components[g.player.id].cur_hp);
        text_printf(&g.stat_win, "ac:%u\n", g.creature_components[g.player.id].ac);

        /*
        text_printf(&g.msg_win, "id = %u\n", g.player.id);
        text_printf(&g.msg_win, "x = %u\n", g.location_components[g.player.id].x);
        text_printf(&g.msg_win, "y = %u\n", g.location_components[g.player.id].y);
        */

        player_system_update();
        
    }

    util_abort("Hello World");

    return 0;
}