/**
 * @file game.c
 * @author Paul  Johnson
 * @brief 
 */

#include "game.h"

#include <stdlib.h>
#include <stdint.h>

#include "game/global_state.h"
#include "core/text.h"


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

/* Speed into turns and ticks conversion table (rounded)
| Speed (ft/turn) | Turns | Ticks (0–9) | Total Ticks   | Relative to Human (30 ft) |
| --------------- | ----- | ----------- | -----------   | ------------------------- |
| 5               | 6     | 0           | 60            |~6× slower                 |
| 10              | 3     | 0           | 30            | ~3× slower                |
| 15              | 2     | 0           | 20            | ~2× slower                |
| 20              | 1     | 5           | 15            | 1.5× slower               |
| 25              | 1     | 2           | 12            | 1.2× slower               |
| 30              | 1     | 0           | 10            | baseline                  |
| 35              | 0     | 9           |  9            | 1.15× faster              |
| 40              | 0     | 8           |  8            | 1.3× faster               |
| 45              | 0     | 7           |  7            | 1.5× faster               |
| 50              | 0     | 6           |  6            | 1.6× faster               |
| 55              | 0     | 5           |  5            | 1.8× faster               |
| 60              | 0     | 4           |  4            | ~2× faster                |
*/
const ticks_t speed_to_ticks_table[SPEED_COUNT] = {
   [SPEED_NONE] = 0,
   [SPEED_5FT]  = 60,
   [SPEED_10FT] = 30,
   [SPEED_15FT] = 20,
   [SPEED_20FT] = 15,
   [SPEED_25FT] = 12,
   [SPEED_30FT] = 10,
   [SPEED_35FT] = 9,
   [SPEED_40FT] = 8,
   [SPEED_45FT] = 7,
   [SPEED_50FT] = 6,
   [SPEED_55FT] = 5,
   [SPEED_60FT] = 4
};

const int8_t modifiers[] = { -5, -4, -4, -3, -3, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10}; 

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/

void game_init(void)
{
    map_init();
}

uint8_t game_roll_dice(dice_roll_t dice)
{
    uint8_t roll = 0;

    text_printf(&g.msg_win, "Roll:%uD%u+%u", dice_roll[dice].n, dice_roll[dice].d, dice_roll[dice].mod);
    for (uint8_t i = 0; i < dice_roll[dice].n; i++)
    {
        roll += 1 + rand() % dice_roll[dice].d;
    }
    roll += dice_roll[dice].mod;

    text_printf(&g.msg_win, "=%d\n", roll);

    return roll;
}

uint8_t game_distance_manhattan(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
{
    uint8_t x = x1 > x2 ? x1 - x2 : x2 - x1;
    uint8_t y  = y1 > y2 ? y1 - y2 : y2 - y1;

    return x + y;
}

ticks_t speed_to_ticks(speed_t speed)
{
    return speed_to_ticks_table[speed];
}

direction_t game_get_dir_or_cancel_b( void )
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