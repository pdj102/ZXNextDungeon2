/**
 * @file zxnext.h
 * @author Paul Johnson 
 * @brief Spectrum Next routines
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
#define KEY_L_A           97
#define KEY_L_C           99
#define KEY_L_D           100
#define KEY_L_E           101
#define KEY_L_G           103
#define KEY_L_I           105
#define KEY_L_L           108
#define KEY_L_O           111
#define KEY_L_T           116
#define KEY_L_U           117

#define KEY_LESSTHAN         60
#define KEY_GREATERTHAN      62
#define KEY_U_C             67
#define KEY_U_E             69

#define PALETTE_GREYSCALE   0b00000000
#define PALETTE_WHITE       0b00010000
#define PALETTE_RED         0b00100000
#define PALETTE_GREEN       0b00110000
#define PALETTE_BLUE        0b01000000
#define PALETTE_YELLOW      0b01010000
#define PALETTE_MAGENTA     0b01100000
#define PALETTE_CYAN        0b01110000
#define PALETTE_ORANGE      0b10000000
#define PALETTE_BROWN       0b10010000
#define PALETTE_LIGHT_GREEN 0b10100000
#define PALETTE_LIGHT_BLUE  0b10110000
#define PALETTE_LIGHT_PURPLE 0b11000000
#define PALETTE_TARGETING_VIS 0b11010000
#define PALETTE_TARGETING_BLOCKED 0b11100000
#define PALETTE_RESERVED    0b11110000

/*
 */

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
 * @brief Initialise the spectrum next hardware
 * 
 */
 void zxnext_init(void);

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
 * @brief Set the attributes of a tile in the ZX Next
 * 
 * @param x 
 * @param y 
 * @param tile_attr 
 */
void zxnext_tilemap_set_attr(uint8_t x, uint8_t y, uint8_t tile_attr);

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

