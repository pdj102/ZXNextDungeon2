/**
 * @file dice.h
 * @author Paul Johnson
 * @brief Dice functions
 */

#ifndef DICE_H
#define DICE_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum dice_e {
    DICE_NONE = 0,
    DICE_1D4,
    DICE_1D6,
    DICE_1D8,
    DICE_1D10,
    DICE_1D20,
    DICE_COUNT
} dice_kind_t;

typedef struct dice_s {
    uint8_t n;
    uint8_t d;
    uint8_t mod;
} dice_roll_t;

/***************************************************
 * public variables
 ***************************************************/
extern const dice_roll_t dice[];

/***************************************************
 * function prototypes
 ***************************************************/
uint8_t dice_roll(dice_kind_t die);

#endif // DICE_H