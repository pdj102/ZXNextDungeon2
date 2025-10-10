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
#include "util.h"
#include "text.h"
#include "entity.h"
#include "PAGE0/init.h"

text_window_t temp_win = {
    .x = 0,
    .y = 0,
    .w = 40,
    .h = 32,
    .c_x = 0,
    .c_y = 0,
    .tile = { .tile_id = 0, .tile_attr = 0 }
};
 
int main(void) {

    init();

    // New game
    entity_init();


    typedef enum {
    ITEM_NONE = 0,
    ITEM_SWORD,
    ITEM_SHIELD,
    ITEM_POTION,
    ITEM_KEY,
    ITEM_KIND_COUNT
    } test_type_t;

    uint16_t s = sizeof(test_type_t);
    text_print_string(&temp_win, "\n\n\n Size of enum: ");
    text_print_uint16(&temp_win, s);

    entity_id_t e1 = entity_create(ENTITY_ITEM, COMPONENT_ITEM);
    text_print_string(&temp_win, "\n\n\nEntity ID: ");
    text_print_uint8(&temp_win, e1);
    text_print_string(&temp_win, "\n");

    entity_id_t e2 = entity_create(ENTITY_ITEM, COMPONENT_ITEM);
    text_print_string(&temp_win, "\n\n\nEntity ID: ");
    text_print_uint8(&temp_win, e2);
    text_print_string(&temp_win, "\n");    

    entity_destroy(e1);

    entity_id_t e3 = entity_create(ENTITY_ITEM, COMPONENT_ITEM);
    text_print_string(&temp_win, "\n\n\nEntity ID: ");
    text_print_uint8(&temp_win, e3);
    text_print_string(&temp_win, "\n");


    util_abort("Hello World");

    while(1)
    {
        // Main loop code here
    }

    return 0;
}