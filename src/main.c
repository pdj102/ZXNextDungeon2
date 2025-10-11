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
#include "location_comp.h"


#include "terrain_map.h"
#include "map_render.h"

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

    typedef enum {
    ITEM_NONE = 0,
    ITEM_SWORD,
    ITEM_SHIELD,
    ITEM_POTION,
    ITEM_KEY,
    ITEM_KIND_COUNT
    } test_type_t;

    // Create some items
    entity_id_t e1 = item_create(ITEM_SWORD, 1);
    place_on_map(e1, 10, 10);
    text_printf(&temp_win, "Item Entity ID: %u\n", e1);

    entity_id_t e2 = item_create(ITEM_POTION, 1);
    place_on_map(e2, 12, 10);
    text_printf(&temp_win, "Item Entity ID: %u\n", e2);

    map_render();

    util_abort("Hello World");

    while(1)
    {
        // Main loop code here
    }

    return 0;
}