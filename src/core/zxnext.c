/**
 * @file zxnext.c
 * @brief Spectrum Next routines
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "zxnext.h"

#include <arch/zxn.h>
#include <input.h>              // Functions for Reading Keyboards, Joysticks and Mice

#include "game/memory_map.h"

#include "core/PAGE36/zxnext_init.h"

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
static  zxnext_tile_t *tilemap_base_p = (volatile zxnext_tile_t *) TILEMAP_BASE;

/***************************************************
 * functions
 ***************************************************/
void zxnext_init(void)
{
    CALL_BANKED_VOID0(PAGE_INIT, zxnext_init_b);
}

 void zxnext_tilemap_clear(const zxnext_tile_t *tile_p)
{
    util_assert(tile_p != NULL);

    zxnext_tile_t *t_p =  ((zxnext_tile_t *) TILEMAP_BASE);

    uint16_t count = TILEMAP_WIDTH * TILEMAP_HEIGHT; 
    uint16_t s;

    for (s = 0; s < count; s++) {
        *t_p++ = *tile_p; /* copy the tile and increment to next tile*/
    }
}

void zxnext_tilemap_set(uint8_t x, uint8_t y, const zxnext_tile_t *tile_p)
{
    util_assert(x < TILEMAP_WIDTH);
    util_assert(y < TILEMAP_HEIGHT);
    util_assert(tile_p != NULL);

    zxnext_tile_t *t_p = tilemap_base_p + ( (y * TILEMAP_WIDTH) + x);

    t_p->tile_id = tile_p->tile_id;
    t_p->tile_attr = tile_p->tile_attr;
}

void zxnext_tilemap_set_attr(uint8_t x, uint8_t y, uint8_t tile_attr)
{
    util_assert(x < TILEMAP_WIDTH);
    util_assert(y < TILEMAP_HEIGHT);

    volatile zxnext_tile_t *t_p = tilemap_base_p + ( (y * TILEMAP_WIDTH) + x);

    t_p->tile_attr = tile_attr;
}


void  zxnext_tilemap_copy(uint8_t fx, uint8_t fy, uint8_t tx, uint8_t ty)
{
    util_assert(fx < TILEMAP_WIDTH);
    util_assert(fy < TILEMAP_HEIGHT);
    util_assert(tx < TILEMAP_WIDTH);
    util_assert(ty < TILEMAP_HEIGHT);
    
    volatile zxnext_tile_t *f_p = tilemap_base_p + ( (fy * TILEMAP_WIDTH) + fx);
    volatile zxnext_tile_t *t_p = tilemap_base_p + ( (ty * TILEMAP_WIDTH) + tx);

    *t_p = *f_p; /* copy the tile */
}

int key_press(void)
{
    int key;

    while ((key = in_inkey()) == 0);  /* loop while no key pressed */
    in_wait_nokey(); /* wait no key */

    return key;
}