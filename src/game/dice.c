/**
 * @file game.c
 * @author Paul  Johnson
 * @brief 
 */

#include "dice.h"

#include <stdlib.h>
#include <stdint.h>

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/
const dice_roll_t dice[DICE_COUNT] = {
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
 * public functions
 ***************************************************/
uint8_t dice_roll(dice_kind_t die)
{
    uint8_t roll = 0;

    for (uint8_t i = 0; i < dice[die].n; i++)
    {
        roll += 1 + rand() % dice[die].d;
    }
    roll += dice[die].mod;

    return roll;
}