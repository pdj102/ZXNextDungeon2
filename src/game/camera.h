/**
 * @file camera.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/


/***************************************************
 * public types
 ***************************************************/
typedef struct {
    uint8_t x;
    uint8_t y;
} camera_t;

/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void camera_init(void);
void camera_center_on(uint8_t x, uint8_t y);

#endif // CAMERA_H
