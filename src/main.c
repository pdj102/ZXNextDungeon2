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
#include "ecs/components/item_comp.h"
#include "ecs/components/creature_comp.h"
#include "ecs/components/location_comp.h"

#include "ecs/entity_factory.h"

#include "ecs/systems/container_system.h"
#include "ecs/systems/player_system.h"
#include "ecs/systems/timer_system.h"

#include "game/map.h"
#include "game/map_render.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/text.h"

#include "core/PAGE0/init.h"


 
int main(void) {

   init_zxnext();
   init_game_state();
   init_ui();
   map_gen();

   text_printf(&g.msg_win, "Global size:%U\n", sizeof(g));
   util_assert(sizeof(g) < 0x3FFF);

    // Create some items
    entity_id_t e1 = entity_factory_create_item(ITEM_SWORD, 1);
    location_add(e1, 10, 10);

    entity_id_t e2 = entity_factory_create_item(ITEM_POTION, 1);
    location_add(e2, 12, 10);

    entity_id_t e3 = entity_factory_create_item(ITEM_KEY, 1);
    // location_add(e3, 14, 10);

    entity_id_t e4 = entity_factory_create_monster(CREATURE_RAT);  
    container_place_item_in_container(e4, e3);
    location_add(e4, 10, 12);

    entity_id_t e5 = entity_factory_create_monster(CREATURE_WITHERWEED);
    location_add(e5, 12, 12);    

    entity_id_t e6 = entity_factory_create_player();
    location_add(e6, 10, 15);

    map_render();

    // Main loop code here
    while(1)
    {
        timer_system_update();

        text_print_string(&g.msg_win, ".");

        player_system_update();

        map_render();        

        // container system cleanup
        container_system_clean_up();
        // entity cleanup
        entity_clean_up();
    }

    util_abort("Hello World");

    return 0;
}