/**
 * @file spatial.h
 * @author Paul Johnson
 * @brief Roguelike spatial general data structures and constants.
 */

#ifndef SPATIAL_H
#define SPATIAL_H

#include <stdint.h>
#include <stdbool.h>

/***************************************************
 * public defines
 ***************************************************/
#define COORD_INVALID_VALUE        255
#define COORD_INVALID ((coord_t){ COORD_INVALID_VALUE, COORD_INVALID_VALUE })

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

typedef struct {
    int x0, y0;
    int x1, y1;
    int dx, dy;
    int sx, sy;
    int err;
    bool finished;
} line_stepper_t;


/***************************************************
 * public variables
 ***************************************************/
extern const vector_t directions[];

/***************************************************
 * function prototypes
 ***************************************************/

inline bool coord_is_valid(coord_t c);

inline bool coord_equal(coord_t a, coord_t b);

coord_t coord_offset(coord_t c, int8_t dx, int8_t dy);

bool are_adjacent(coord_t a, coord_t b);

inline bool in_range(coord_t a, coord_t b, uint8_t range);

inline bool in_range_manhattan(coord_t a, coord_t b, uint8_t range);

uint8_t spatial_distance_manhattan(coord_t a, coord_t b);

direction_t spatial_get_dir_or_cancel_b( void );

void line_stepper_init(line_stepper_t *ls, int x0, int y0, int x1, int y1);

bool line_stepper_step(line_stepper_t *ls);

#endif // SPATIAL_H