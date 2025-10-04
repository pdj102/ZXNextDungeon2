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

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/map.h"
#include "game/map_render.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/text.h"
#include "core/core_init_bank.h"

void clean_up_and_destroy(void);
 
int main(void) {

   core_init_bank();

   entity_init();

   components_init();

   systems_init();

   game_init();


   map_gen();

   util_info("Debug build");
   text_printf(&g.msg_win, "Global size:%U\n", sizeof(g));
   util_assert(sizeof(g) < 0x3FFF);


    entity_id_t e1 = system_item_create(ITEM_SHORT_SWORD, 1);
    comp_location_add(e1, 10, 10);

    entity_id_t e2 = system_item_create(ITEM_POTION_OF_HEALING, 1);
    comp_location_add(e2, 12, 10);

    entity_id_t e3 = system_item_create(ITEM_KEY, 1);

    entity_id_t e4 = system_monster_create(CREATURE_RAT);  
    system_container_add(e4, e3);
    comp_location_add(e4, 10, 12);

    entity_id_t e5 = system_monster_create(CREATURE_WITHERWEED);
    comp_location_add(e5, 12, 12);    

    g.player.id = ENTITY_ID_INVALID;
    entity_id_t e6 = system_monster_create_player();
    comp_location_add(e6, 10, 15);

    entity_id_t e7 = system_item_create(ITEM_BREAD, 1);
    comp_location_add(e7, 6, 15);

    util_info("map render");

    map_render();

    while(1)
    {
        system_timer_update();

        system_player_update();

        map_render();        

        clean_up_and_destroy();
    }

    util_abort("Hello World");

    return 0;
}


void clean_up_and_destroy(void)
{
    uint8_t i = 0;
    entity_id_t id;

    /* Run clean up for each entity marked for destruction */
    /* Note: clean up may append more entities to the list for destruction */
    /* So we need to iterate until the list is empty */
    /* Do not destroy anything yet */

    while (g.entity_components.destroy_head > i)
    {
        id = g.entity_components.destroy_list[i];
        // text_printf(&g.msg_win, "%d entities to cleanup\n", g.entity_components.destroy_head);
        
        util_assert(entity_has_flag(id, FLAG_PENDING_DESTROY));
        system_container_clean_up(id);
        // system_equipment_clean_up(id);

        i++;
    }

    /* Now all entities are marked for destruction and cleanup has been run*/
    /* Finalise the destruction */

    i = 0;
    while ( g.entity_components.destroy_head >  i)
    {
        id = g.entity_components.destroy_list[i];
        // text_printf(&g.msg_win, "%d entities to destroy\n", g.entity_components.destroy_head);
        util_assert(entity_has_flag(id, FLAG_PENDING_DESTROY));
        entity_destroy(id);

        i++;
    }
    g.entity_components.destroy_head = 0;
}