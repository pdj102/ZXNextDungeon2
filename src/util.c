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

#include <stdlib.h>
#include <stdint.h>

#include "global_state.h"
#include "text.h"
#include "zxnext.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/
const vector_t directions[DIRECTION_COUNT] = {
    [DIRECTION_NONE] = {0, 0},
    [DIRECTION_NORTH] = {0, -1},
    [DIRECTION_WEST] = {-1, 0},
    [DIRECTION_SOUTH] = {0, 1},
    [DIRECTION_EAST] = {1, 0}
};

const dice_t dice_roll[DICE_COUNT] = {
    [DICE_NONE] = {0, 0, 0},
    [DICE_1D4] = {1, 4, 0},
    [DICE_1D6] = {1, 6, 0},
    [DICE_1D8] = {1, 8, 0},
    [DICE_1D10] = {1, 10, 0},
    [DICE_1D20] = {1, 20, 0}
};


/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/

uint8_t util_roll_dice(dice_roll_t dice)
{
    uint8_t roll;

    for (uint8_t i = 0; i < dice_roll[dice].n; i++)
    {
        roll += 1 + rand() % dice_roll[dice].d;
    }
    roll += dice_roll[dice].mod;

    return roll;
}

uint8_t util_distance_manhattan(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
{
    uint8_t x = x1 > x2 ? x1 - x2 : x2 - x1;
    uint8_t y  = y1 > y2 ? y1 - y2 : y2 - y1;

    return x + y;
}

direction_t util_get_dir_or_cancel_b( void )
{
    unsigned int key;

    key = key_press();   

    switch (key)
    {

    case KEY_DOWN: // down
        return DIRECTION_SOUTH;

    case KEY_UP: // up
        return DIRECTION_NORTH;

    case KEY_LEFT: // left
        return DIRECTION_WEST;

    case KEY_RIGHT: // right
        return DIRECTION_EAST;

    default:
        return DIRECTION_NONE;
    }
}

void util_assert_f(const char *message, const char *file, unsigned line)
{
    text_printf(&g.assert_win, "ASSERT FAIL: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);
}

void util_abort_f(const char *message, const char *file, unsigned line)
{
    text_printf(&g.assert_win, "ABORT: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);    
}