/**
 * @file main.c
 * @author Paul Johnson 
 * @brief ZX Next Dungeon II
 * @version 0.1
 * @date 2025-10-04
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
 
int main(void) {

    init();

    // New game
    entity_init();

    util_abort("Hello World");

    while(1)
    {
        // Main loop code here
    }

    return 0;
}