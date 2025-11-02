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

/*
 * Memory map - Next 8KB banking scheme
 *
 * slot 1 (0x000)     Fixed global game state (by default would contain the ROM)
 * slot 2 (0x2000)    Fixed global game state (by default would contain the ROM) 
 * slot 3 (0x4000)    Fixed tilemap and tilesets (bank 5)
 * slot 4 (0x6000)    Fixed tilemap and tilesets (bank 5)
 * slot 5 (0x8000)    Fixed non banking core game code (bank 2)
 * slot 6 (0xa000)    Fixed non banking core game code (bank 2)
 * slot 7 (0xc000)    Banked game code and data (bank 0) 
 * slot 8 (0xe000)    Banked game code and data (bank 0)
 *
 *
 * 0x4000 - 0x49FF      Tilemap - 40 * 32 tiles * 2 bytes per tile = 0xA00 (2,560) bytes
 * 0x4a00 - 0x69FF      Tele definitions - 256 tiles * 32 bytes per tile definition = 0x2000 (8,192) bytes
 * 0x6a00 - 0x7FFF      NOT USED
 * 
 * 0xbfff               Top of stack (TODO move stack to unused space at top of bank 5)
 */

 /*
  * Page numbers and usage
  *
  * NB 
  *     use even page numbers for default ORG 0xc000 e.g. page 30, 32
  *     use odd page numbers for default ORG 0xe000 e.g. page 31, 33
  */
#define PAGE_INIT           0
#define PAGE_PALETTE        1
#define PAGE_CREATURE_BASE  30
#define PAGE_ITEM_BASE      32


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

