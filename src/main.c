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

#include "ecs/entity.h"
#include "ecs/item_comp.h"
#include "ecs/creature_comp.h"
#include "ecs/location_comp.h"

#include "ecs/entity_factory.h"

#include "ecs/player_system.h"

#include "game/map_terrain.h"
#include "game/map_render.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/text.h"

#include "core/PAGE0/init.h"


 
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
        map_render();

        text_cls(&g.stat_win);
        text_printf(&g.stat_win, "hp:%u\n", g.creature_components[g.player.id].cur_hp);
        text_printf(&g.stat_win, "ac:%u\n", g.creature_components[g.player.id].ac);

        player_system_update();        
    }

    util_abort("Hello World");

    return 0;
}