/**
 * @file game.h
 * @author Paul Johnson
 * @brief Roguelike game general data structures and constants.
 */

#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum direction_e {
    DIRECTION_NONE = 0,
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_COUNT
} direction_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} coord_t;

typedef struct {
    int8_t x;
    int8_t y;
} vector_t;

typedef enum dice_e {
    DICE_NONE = 0,
    DICE_1D4,
    DICE_1D6,
    DICE_1D8,
    DICE_1D10,
    DICE_1D20,
    DICE_COUNT
} dice_roll_t;

typedef struct dice_s {
    uint8_t n;
    uint8_t d;
    uint8_t mod;
} dice_t;

typedef uint8_t ticks_t;

typedef enum creature_speed_e {
    SPEED_NONE = 0,
    SPEED_5FT, 
    SPEED_10FT,
    SPEED_15FT,
    SPEED_20FT,
    SPEED_25FT,
    SPEED_30FT,
    SPEED_35FT,
    SPEED_40FT,
    SPEED_45FT,
    SPEED_50FT,
    SPEED_55FT,
    SPEED_60FT,
    SPEED_COUNT
} speed_t;

/***************************************************
 * public variables
 ***************************************************/
extern const vector_t directions[];
extern const dice_t dice[];
extern const int8_t modifiers[]; 

/***************************************************
 * function prototypes
 ***************************************************/

void game_init(void);

uint8_t game_roll_dice(dice_roll_t dice);

direction_t game_get_dir_or_cancel_b( void );

ticks_t speed_to_ticks(speed_t speed);

#endif // GAME_H