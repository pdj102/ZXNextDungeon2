/**
 * @file zxnext.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "zxnext.h"

#include <arch/zxn.h>

#include "util.h"

#define REG_ULA_CONTROL 0x68 
#define RUC_DISABLE_ULA_OUTPUT 0b10000000 /* bit 7 = 1 to disable ULA output */

#define RTM_28MHZ 0b00000011 /* bits 1-0 = 11 for 28MHz */

#define REG_TILEMAP_CONTROL 0x6B /* Tilemap Control Register */
#define RTC_ENABLE     0b10000000 /* bit 7 = 1 to enable the tilemap */
#define RTC_80X32      0b01000000 /* bit 6 = 0 for 40x32, 1 for 80x32 */
#define RTC_NO_ATTR    0b00100000 /* bit 5 = 1 to eliminate the attribute entry in the tilemap */
#define RTC_PALETTE_1  0b00010000 /* bit 4 = palette select, 0 = first tilemap palette 1 = second*/
#define RTC_TEXT       0b00000100 /* bit 3 = 0 for graphics, 1 for text mode */
#define RTC_512_TILES  0b00000010 /* bit 1 = 1 to activate 512 tile mode */
#define RTC_ON_TOP     0b00000001 /* bit 0 = 1 to force tilemap on top of ULA */

#define REG_TILEMAP_BASE_ADDR 0x6E /*  Tilemap Base Address Register */

#define REG_TILEDEFS_BASE_ADDR 0x6F /* Tile Definitions Base Address Register */

#define TILEMAP_BASE 0x4000 /* The base address of the tilemap in memory */
#define TILEMAP_WIDTH 40    /* The width of the tilemap in tiles */
#define TILEMAP_HEIGHT 32   /* The height of the tilemap in tiles */


/***************************************************
 * private variables - static
 ***************************************************/

/**
 * @brief Pointer to the base of the ZXnext tilemap 
 * 
 */
static zxnext_tile_t *tilemap_base_p = (zxnext_tile_t *) TILEMAP_BASE;


void zxnext_init(void) {
    /* set CPU speed 28MHz */
    ZXN_WRITE_REG(REG_TURBO_MODE, RTM_28MHZ);

    /* disable RAM contention */
    ZXN_WRITE_REG(REG_PERIPHERAL_3, (ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION));

    /* Disable the ZXnext ULA screen */
    ZXN_WRITE_REG(REG_ULA_CONTROL, (ZXN_READ_REG(REG_ULA_CONTROL) | RUC_DISABLE_ULA_OUTPUT));

    /* 
     * Set the Tilemap Control Register
     *
     * bit 7    = 1 to enable tilemap
     * bit 6    = 0 for 40x32, 1 for 80x32
     * bit 5    = 1 to eliminate the attribute entry in the tilemap
     * bit 4    = palette select
     * bits 3-2 = Reserved set to 0
     * bit 1    = 1 to activate 512 tile mode
     * bit 0    = 1 to force tilemap on top of ULA    
     */
    ZXN_WRITE_REG(REG_TILEMAP_CONTROL, RTC_ENABLE | RTC_512_TILES | RTC_ON_TOP);

    /*
     * Set the ZXnext tilemap base address register 
     *
     * Sets the tilemap base address offset within bank 5
     *
     * Bank 5 is located at 0x4000 - 0x7fff
     * The ULA screen is located 0x4000 - 0x5FFF (7 KiB)
     * The ULA screen is not required and has been disabled so we can write the tilemap at 0x4000
     * The tilemap is 40 * 32 tiles * 2 bytes per tile = 0xA00 (2,560) bytes
     *
     * 0x6E is set with the MSB which represents an n x 256 byte offset within bank 5
     * For example, to load the tilemap at 0x6000 the offset would be 32 decimal (0x6000 - 0x4000) / 0x100 = 0x20 (32)
     *
     * Write the tilemap to 0x4000 - 0x49FF (offset 0 in bank 5)
     */
    ZXN_NEXTREG(REG_TILEMAP_BASE_ADDR, 0);

/*
     * Set the ZXnext register for the base memory address of the tile definitions
     * 
     * 0x6F - Tile definitions base address
     *
     * sets the tile definitions base address offset within bank 5 (or bank 7 if bit 7 is set)
     * Bank 5 is located at 0x4000 - 0x7fff
     * The ULA screen is located 0x4000 - 0x5FFF (7 KiB) 
     * The ULA screen is not required and has been disabled so we can write the tilemap at 0x4000
     * The tilemap is 2,560 (0xa00) bytes so occupies 0x4000 - 0x49ff
     * Loading the tile definitions at or above 0x4A00 avoids it
     * 0x6F is set with the MSB which represents an n x 256 byte offset. (0x4A00 - 0x4000) / 0x100 = 10 decimal 
     * 
     */
    ZXN_NEXTREG( REG_TILEDEFS_BASE_ADDR , 10);
}

void zxnext_tilemap_clear(const zxnext_tile_t *tile_p)
{
    zxnext_tile_t *t_p = tilemap_base_p;

    for (uint16_t s = 0; s < TILEMAP_WIDTH * TILEMAP_HEIGHT; s++) {
        t_p->tile_id = tile_p->tile_id;
        t_p->tile_attr = tile_p->tile_attr;
        t_p++;
    }
}

void zxnext_tilemap_set(uint8_t x, uint8_t y, const zxnext_tile_t *tile_p)
{
    util_assert(x < TILEMAP_WIDTH);
    util_assert(y < TILEMAP_HEIGHT);
    util_assert(tile_p != NULL);

    zxnext_tile_t *t_p = tilemap_base_p + ( (y * TILEMAP_WIDTH) + x);

    *t_p = *tile_p; /* copy the tile */
}

void  zxnext_tilemap_copy(uint8_t fx, uint8_t fy, uint8_t tx, uint8_t ty)
{
    util_assert(fx < TILEMAP_WIDTH);
    util_assert(fy < TILEMAP_HEIGHT);
    util_assert(tx < TILEMAP_WIDTH);
    util_assert(ty < TILEMAP_HEIGHT);
    
    zxnext_tile_t *f_p = tilemap_base_p + ( (fy * TILEMAP_WIDTH) + fx);
    zxnext_tile_t *t_p = tilemap_base_p + ( (ty * TILEMAP_WIDTH) + tx);

    *t_p = *f_p; /* copy the tile */
}
