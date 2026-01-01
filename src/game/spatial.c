/**
 * @file spatial.c
 * @author Paul  Johnson
 * @brief 
 */

#include "spatial.h"

#include "core/zxnext.h"

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
const vector_t directions[DIRECTION_COUNT] = {
    [DIRECTION_NONE] = {0, 0},
    [DIRECTION_NORTH] = {0, -1},
    [DIRECTION_WEST] = {-1, 0},
    [DIRECTION_SOUTH] = {0, 1},
    [DIRECTION_EAST] = {1, 0}
};

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
inline bool coord_is_valid(coord_t c)
{
    return c.x != COORD_INVALID_VALUE;
}

inline bool coord_equal(coord_t a, coord_t b)
{
    return ((a.x == b.x) && (a.y == b.y));
}

coord_t coord_offset(coord_t c, int8_t dx, int8_t dy)
{
    coord_t o;

    o.x = c.x + dx;
    o.y = c.y + dy;

    return o;
}

bool are_adjacent(coord_t a, coord_t b)
{
    int8_t dx = a.x - b.x;
    int8_t dy = a.y - b.y;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    return (dx <= 1 && dy <= 1 && (dx | dy));
}

/*
 * @brief Determines if two points are in range using chebyshev distance calculation
 */
inline bool in_range(coord_t a, coord_t b, uint8_t range)
{
    uint8_t dx = (a.x > b.x) ? (a.x - b.x) : (b.x - a.x);
    uint8_t dy = (a.y > b.y) ? (a.y - b.y) : (b.y - a.y);

    return (dx <= range && dy <= range);
}

/*
 * @brief Determines if two points are in range using manhatten distance calculation
 */
inline bool in_range_manhattan(coord_t a, coord_t b, uint8_t range)
{
    uint8_t dx = (a.x > b.x) ? (a.x - b.x) : (b.x - a.x);
    uint8_t dy = (a.y > b.y) ? (a.y - b.y) : (b.y - a.y);

    return (dx + dy) <= range;
}

// uint8_t spatial_distance_manhattan(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
// uint8_t x = x1 > x2 ? x1 - x2 : x2 - x1;
// uint8_t y  = y1 > y2 ? y1 - y2 : y2 - y1;

uint8_t distance_manhattan(coord_t a, coord_t b)
{
    uint8_t x = (a.x > b.x) ? (a.x - b.x) : (b.x - a.x);
    uint8_t y = (a.y > b.y) ? (a.y - b.y) : (b.y - a.y);

    return x + y;
}

void line_stepper_init(line_stepper_t *ls, int x0, int y0, int x1, int y1)
{
    ls->x0 = x0;
    ls->y0 = y0;
    ls->x1 = x1;
    ls->y1 = y1;

    ls->dx = abs(x1 - x0);
    ls->dy = abs(y1 - y0);

    ls->sx = (x0 < x1) ? 1 : -1;
    ls->sy = (y0 < y1) ? 1 : -1;

    ls->err = ls->dx - ls->dy;
    ls->finished = false;
}

bool line_stepper_step(line_stepper_t *ls)
{
    if (ls->finished)
        return false;

    if (ls->x0 == ls->x1 && ls->y0 == ls->y1) {
        ls->finished = true;
        return false;    // nothing more to step
    }

    int e2 = ls->err << 1;

    if (e2 > -ls->dy) {
        ls->err -= ls->dy;
        ls->x0 += ls->sx;
    }

    if (e2 < ls->dx) {
        ls->err += ls->dx;
        ls->y0 += ls->sy;
    }

    return true;   // successfully stepped
}


