/**
 * @file zxnext.h
 * @author Paul Johnson 
 * @brief ZX Next specific functions
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ZXNEXT_H
#define ZXNEXT_H

#include <stdint.h>

#define KEY_UP          11
#define KEY_DOWN        10
#define KEY_LEFT        8
#define KEY_RIGHT       9
#define KEY_A           97
#define KEY_D           100
#define KEY_G           103

/***************************************************
 * public types
 ***************************************************/

/**
 * @brief A structure to represent a ZX Next tilemap tile
 * 
 */
typedef struct zxnext_tile {
    uint8_t tile_id;            /**< the id of the tile definition */
    uint8_t tile_attr;          /**< the tile attributes */
} zxnext_tile_t;

/***************************************************
 * public function prototypes
 ***************************************************/



/**
 * @brief Clear the ZX Next tilemap by setting all tiles to the specified tile
 * 
 */
void zxnext_tilemap_clear(const zxnext_tile_t *tile);

/**
 * @brief Set a tile in the ZX Next tilemap at the specified (x,y) position
 * 
 */
void zxnext_tilemap_set(uint8_t x, uint8_t y, const zxnext_tile_t *tile_p);

/**
 * @brief Copy a tile from one position to another in the ZX Next tilemap
 * 
 */
void  zxnext_tilemap_copy(uint8_t fx, uint8_t fy, uint8_t tx, uint8_t ty);

/**
 * @brief Wait for a key press
 * 
 * @return int 
 */
int key_press(void);

#endif // ZXNEXT_H
