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

#include "entity_factory.h"

#include "location_comp.h"

#include "terrain_map.h"
#include "map_render.h"

#include "global_state.h"

#include "util.h"
#include "text.h"

#include "PAGE0/init.h"

text_window_t temp_win = {
    .x = 0,
    .y = 24,
    .w = 40,
    .h = 8,
    .c_x = 0,
    .c_y = 0,
    .tile = { .tile_id = ' ', .tile_attr = 0 }
};
 
int main(void) {

    init();
    zxnext_tilemap_clear(&(temp_win.tile));

    // New game
    entity_init();
    item_init();
    location_init();
    terrain_map_init();
    g.player = ENTITY_ID_INVALID;

    // Create some items
    entity_id_t e1 = entity_factory_create_item(ITEM_SWORD, 1);
    location_place_on_map(e1, 10, 10);
    text_printf(&temp_win, "Item Entity ID: %u\n", e1);

    entity_id_t e2 = entity_factory_create_item(ITEM_POTION, 1);
    location_place_on_map(e2, 12, 10);
    text_printf(&temp_win, "Item Entity ID: %u\n", e2);

    entity_id_t e3 = entity_factory_create_item(ITEM_KEY, 1);
    text_printf(&temp_win, "Item Entity ID: %u\n", e3);    
    location_place_on_map(e3, 14, 10);

    entity_id_t e4 = entity_factory_create_monster(CREATURE_RAT);
    text_printf(&temp_win, "Item Entity ID: %u\n", e4);    
    location_place_on_map(e4, 10, 12);

    entity_id_t e5 = entity_factory_create_player();
    text_printf(&temp_win, "Item Entity ID: %u\n", e5);    
    location_place_on_map(e5, 10, 15);

    map_render();

    while(1)
    {
        // Main loop code here
    }

    util_abort("Hello World");

    return 0;
}