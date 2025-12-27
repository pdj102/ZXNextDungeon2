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

#include "game/ui.h"
#include "game/map.h"
#include "game/map_render.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/text.h"
#include "core/core_init_bank.h"

static void clean_up_and_destroy(void);
static void turn(void);
 
int main(void) {

   core_init_bank();

   entity_init();

   component_init();

   systems_init();

   game_init();

   map_gen();

   util_info("Debug build");
   text_printf(&g.msg_win, "Global size:%U\n", sizeof(g));
   util_assert(sizeof(g) < 0x3FFF);


    entity_id_t e1 = system_item_create(ITEM_SHORT_SWORD, 1);
    system_movement_place(e1, 10, 10);

    entity_id_t e2 = system_item_create(ITEM_POTION_OF_HEALING, 1);
    system_movement_place(e2, 12, 10);

    entity_id_t e3 = system_item_create(ITEM_KEY, 1);

    entity_id_t e4 = system_monster_create(CREATURE_RAT);  
    system_container_add(e4, e3);
    system_movement_place(e4, 10, 12);

    entity_id_t e5 = system_monster_create(CREATURE_WITHERWEED);
    system_movement_place(e5, 12, 12);    

    g.player.id = ENTITY_ID_INVALID;
    entity_id_t e6 = system_monster_create_player();
    system_movement_place(e6, 10, 15);

    entity_id_t e7 = system_item_create(ITEM_BREAD, 1);
    system_movement_place(e7, 6, 15);

    entity_id_t e8 = system_item_create(ITEM_RING_OF_STRENGTH, 1);
    system_movement_place(e8, 7, 15);

    util_info("map render");

    map_render();

    ui_update_primary_stats();
    ui_update_secondary_stats();
    ui_update_resource_stats();

    while(1)
    {
        system_timer_update();

        turn();

        map_render();

        if (g.stat_win.dirty == 1)
        {
            ui_update_primary_stats();
            ui_update_secondary_stats();
            ui_update_resource_stats();
            g.stat_win.dirty = 0;
        }

        clean_up_and_destroy();
    }

    util_abort("Hello World");

    return 0;
}

/*
 * @brief Entities take there turn
 */
static void turn(void)
{
    for (uint8_t id = 0; id < MAX_ENTITIES; id++)
    {
        if (entity_has_component(id, COMPONENT_TIMER) && system_timer_has_fired(id))
        {
            system_timer_reset(id);

            if (entity_has_component(id, COMPONENT_PLAYER))
            {
                system_player_update();
            }
            else if (entity_has_component(id, COMPONENT_AI))
            {
                // system_ai_process_entity_turn(id);
            }

            if (entity_has_component(id, COMPONENT_ACTIVE_EFFECT))
            {
                system_effect_process_entity_turn(id);
            }
        }

    }
}


static void clean_up_and_destroy(void)
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
        text_printf(&g.msg_win, "%d entities to cleanup\n", g.entity_components.destroy_head);
        
        util_assert(entity_has_flag(id, FLAG_PENDING_DESTROY));
        util_assert(entity_has_flag(id, FLAG_IN_USE));
        system_container_clean_up(id);
        system_effect_cleanup_entity(id);
        system_movement_cleanup(id);
        system_timer_cleanup(id);
        system_equipment_cleanup(id);

        i++;
    }

    /* Now all entities are marked for destruction and cleanup has been run*/
    /* Finalise the destruction */
    entity_cleanup();
}