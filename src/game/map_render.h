/**
 * @file map_render.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_RENDER_H
#define MAP_RENDER_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
typedef struct {
    uint8_t x;
    uint8_t y;
} camera_t;
/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void map_render(void);

#endif // MAP_RENDER_H
