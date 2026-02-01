/**
 * @file camera.c
 * @author Paul Johnson
 * @brief Game camera 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/camera.h"

#include <stdint.h>

#include "game/global_state.h"

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
void camera_init(void);
void camera_center_on(uint8_t x, uint8_t y);

/***************************************************
 * public functions
 ***************************************************/

void camera_init(void)
{
    g.camera.x = 0;
    g.camera.y = 0;
}

void camera_center_on(uint8_t x, uint8_t y)
{

}

/***************************************************
 * private functions
 ***************************************************/

