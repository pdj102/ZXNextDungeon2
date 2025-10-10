/**
 * @file util.c
 * @author Paul  Johnson
 * @brief 
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "util.h"
#include "text.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/
text_window_t assert_win = {
    .x = 0,
    .y = 0,
    .w = 40,
    .h = 32,
    .c_x = 0,
    .c_y = 0,
    .tile = { .tile_id = 0, .tile_attr = 0 }
};

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/

void util_assert_f(const char *message, const char *file, unsigned line)
{
    text_printf(&assert_win, "ASSERT FAIL: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);
}

void util_abort_f(const char *message, const char *file, unsigned line)
{
    text_printf(&assert_win, "ABORT: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);    
}