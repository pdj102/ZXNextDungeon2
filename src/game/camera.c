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
#include <stdbool.h>

#include "game/global_state.h"
#include "game/map.h"
#include "game/map_render.h"

#include "ecs/entity.h"
#include "ecs/components/components.h"

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void camera_clamp(uint8_t x, uint8_t y, uint8_t *out_x, uint8_t *out_y);

/***************************************************
 * public functions
 ***************************************************/

void camera_init(void)
{
    g.camera.x = 0;
    g.camera.y = 0;
    g.camera.mode = CAMERA_MODE_FOLLOW_PLAYER;
}

void camera_center_on(uint8_t x, uint8_t y)
{
    uint8_t camera_x;
    uint8_t camera_y;

    /* Calculate position to center viewport on target */
    /* Handle underflow by checking before subtraction */
    if (x >= VIEW_WIDTH / 2) {
        camera_x = x - (VIEW_WIDTH / 2);
    } else {
        camera_x = 0;
    }

    if (y >= VIEW_HEIGHT / 2) {
        camera_y = y - (VIEW_HEIGHT / 2);
    } else {
        camera_y = 0;
    }

    /* Clamp to keep viewport in bounds */
    camera_clamp(camera_x, camera_y, &g.camera.x, &g.camera.y);

    /* Mark main window for re-render */
    g.main_win.dirty = 1;
}

void camera_set_mode(camera_mode_t mode)
{
    g.camera.mode = mode;
}

camera_mode_t camera_get_mode(void)
{
    return g.camera.mode;
}

void camera_update(void)
{
    /* Only update if in FOLLOW_PLAYER mode */
    if (g.camera.mode != CAMERA_MODE_FOLLOW_PLAYER)
        return;

    /* Follow the player */
    if (g.player.id != ENTITY_ID_INVALID &&
        entity_has_component(g.player.id, COMPONENT_LOCATION))
    {
        uint8_t px = g.location_components[g.player.id].coord.x;
        uint8_t py = g.location_components[g.player.id].coord.y;
        camera_center_on(px, py);
    }
}

bool camera_map_to_screen(uint8_t map_x, uint8_t map_y, uint8_t *screen_x, uint8_t *screen_y)
{
    uint8_t sx = map_x - g.camera.x;
    uint8_t sy = map_y - g.camera.y;

    /* Relies on unsigned underflow for bounds checking */
    if (sx >= VIEW_WIDTH || sy >= VIEW_HEIGHT)
        return false;

    *screen_x = sx;
    *screen_y = sy;
    return true;
}

/***************************************************
 * private functions
 ***************************************************/

/**
 * @brief Clamp camera position to keep viewport within map bounds
 * @param x Desired camera x position
 * @param y Desired camera y position
 * @param out_x Output: clamped x position
 * @param out_y Output: clamped y position
 */
static void camera_clamp(uint8_t x, uint8_t y, uint8_t *out_x, uint8_t *out_y)
{
    /* Clamp X: viewport must not exceed MAP_WIDTH */
    if (x + VIEW_WIDTH > MAP_WIDTH) {
        *out_x = MAP_WIDTH - VIEW_WIDTH;
    } else {
        *out_x = x;
    }

    /* Clamp Y: viewport must not exceed MAP_HEIGHT */
    if (y + VIEW_HEIGHT > MAP_HEIGHT) {
        *out_y = MAP_HEIGHT - VIEW_HEIGHT;
    } else {
        *out_y = y;
    }
}

