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
#include "zxnext.h"
#include "util.h"

#include "text.h"
 
void init(void) {
    // Initialization code here

    zxnext_init();
}

int main(void) {

    init();

    util_abort("Hello World");

    while(1)
    {
        zx_border(INK_YELLOW);
        zx_border(INK_GREEN);
        // Main loop code here
    }

    return 0;
}