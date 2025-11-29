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

#include "core/systems_dispatch.h"

#include "game/map.h"
#include "game/map_render.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/text.h"
#include "core/init_bank.h"
#include "core/systems_dispatch.h"


 
int main(void) {

   init_zxnext_bank();
   init_game_state_bank();
   init_ui_bank();
   map_gen();

   text_printf(&g.msg_win, "Global size:%U\n", sizeof(g));
   util_assert(sizeof(g) < 0x3FFF);

    // Create some items
    entity_id_t e1 = system_equipment_create(ITEM_SHORT_SWORD, 1);
    location_add(e1, 10, 10);

    entity_id_t e2 = system_equipment_create(ITEM_POTION_OF_HEALING, 1);
    location_add(e2, 12, 10);

    entity_id_t e3 = system_equipment_create(ITEM_KEY, 1);
    // location_add(e3, 14, 10);

    entity_id_t e4 = system_monster_create(CREATURE_RAT);  
    system_container_place_item_in(e4, e3);
    location_add(e4, 10, 12);

    entity_id_t e5 = system_monster_create(CREATURE_WITHERWEED);
    location_add(e5, 12, 12);    

    entity_id_t e6 = system_monster_create_player();
    location_add(e6, 10, 15);

    map_render();

    // Main loop code here
    while(1)
    {
        system_timer_update();

        text_print_string(&g.msg_win, ".");

        system_player_update();

        map_render();        

        // container system cleanup
        system_container_clean_up();
        // entity cleanup
        entity_clean_up();
    }

    util_abort("Hello World");

    return 0;
}