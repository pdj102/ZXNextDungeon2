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


 
int main(void) {

    init();

g.msg_win.x = 0;
g.msg_win.y = 24;
g.msg_win.w = 40;
g.msg_win.h = 8;
g.msg_win.c_x = 0;
g.msg_win.c_y = 0;
g.msg_win.tile.tile_id = ' ';
g.msg_win.tile.tile_attr = 0;
    
    zxnext_tilemap_clear(&(g.msg_win.tile));

    // New game
    entity_init();
    item_init();
    location_init();
    player_ctrl_init();
    map_terrain_init();

    // Create some items
    entity_id_t e1 = entity_factory_create_item(ITEM_SWORD, 1);
    location_add(e1, 10, 10);
    text_printf(&g.msg_win, "Item Entity ID: %u\n", e1);

    entity_id_t e2 = entity_factory_create_item(ITEM_POTION, 1);
    location_add(e2, 12, 10);
    text_printf(&g.msg_win, "Item Entity ID: %u\n", e2);

    entity_id_t e3 = entity_factory_create_item(ITEM_KEY, 1);
    text_printf(&g.msg_win, "Item Entity ID: %u\n", e3);    
    location_add(e3, 14, 10);

    entity_id_t e4 = entity_factory_create_monster(CREATURE_RAT);
    text_printf(&g.msg_win, "Item Entity ID: %u\n", e4);    
    location_add(e4, 10, 12);

    entity_id_t e5 = entity_factory_create_player();
    text_printf(&g.msg_win, "Item Entity ID: %u\n", e5);    
    location_add(e5, 10, 15);

    map_render();

    while(1)
    {
        // Main loop code here
        /* energy system */
        /* player control system*/
        // player_control_system_run();
        map_render();

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