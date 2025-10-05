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

/***************************************************
 * private defines
 ***************************************************/
#define TILEMAP_BASE 0x4000 /* The base address of the tilemap in memory */
#define TILEMAP_WIDTH 40    /* The width of the tilemap in tiles */
#define TILEMAP_HEIGHT 32   /* The height of the tilemap in tiles */

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables 
 ***************************************************/

/**
 * @brief Pointer to the base of the ZXnext tilemap 
 * 
 */
static zxnext_tile_t *tilemap_base_p = (zxnext_tile_t *) TILEMAP_BASE;

/***************************************************
 * functions
 ***************************************************/
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

