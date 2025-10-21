/**
 * @file util.h
 * @author Paul Johnson
 * @brief 
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UTIL_H
#define UTIL_H

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

/***************************************************
 * public variables
 ***************************************************/
extern const vector_t directions[];
extern const dice_t dice[];


/***************************************************
 * function prototypes
 ***************************************************/

direction_t get_dir_or_cancel_b( void );

void util_assert_f(const char *message, const char *file, unsigned line);

void util_abort_f(const char *message, const char *file, unsigned line);

/***************************************************
 * macros
 ***************************************************/
/* If DEBUG defined, enable assert */
#ifdef NDEBUG
    #define util_assert(_Expression) ((void)0)
#else /* !defined (NDEBUG) */
    #define util_assert(_Expression) \
        do { \
            if (!(_Expression)) \
                util_assert_f(#_Expression, __FILE__, __LINE__); \
        } while(0)
#endif /* !defined (NDEBUG) */

#define util_abort(message) util_abort_f(message, __FILE__,__LINE__);

#endif // UTIL_H