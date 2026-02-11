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
#include <stdbool.h>

/***************************************************
 * public defines
 ***************************************************/


/***************************************************
 * public types
 ***************************************************/
typedef enum {
    CAMERA_MODE_FOLLOW_PLAYER,  /* Default: follows player automatically */
    CAMERA_MODE_MANUAL,         /* Manual control (for debugging/future features) */
    CAMERA_MODE_TARGETING       /* Targeting mode (used by look/attack commands) */
} camera_mode_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    camera_mode_t mode;
} camera_t;

/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void camera_init(void);
void camera_center_on(uint8_t x, uint8_t y);
void camera_set_mode(camera_mode_t mode);
camera_mode_t camera_get_mode(void);
void camera_update(void);
bool camera_map_to_screen(uint8_t map_x, uint8_t map_y, uint8_t *screen_x, uint8_t *screen_y);

#endif // CAMERA_H
