/**
 * @file init.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "init.h"

#include <arch/zxn.h>
/* #include <config_zxn.h> */
#include <stdint.h>

#include "../../ecs/entity.h"

#include "../../ecs/components/contained_comp.h"
#include "../../ecs/components/container_comp.h"
#include "../../ecs/components/creature_comp.h"
#include "../../ecs/components/item_comp.h"
#include "../../ecs/components/location_comp.h"
#include "../../ecs/components/player_ctrl_comp.h"
#include "../../ecs/components/renderable_comp.h"

#include "../../core/systems_dispatch.h"
#include "../../game/map_terrain.h"
#include "../../game/map_render.h"
#include "../../game/global_state.h"

#include "../zxnext.h"


/***************************************************
 * private defines
 ***************************************************/
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

#define RPC_SELECT_TILEMAP_PALETTE_0  0b00110000 /* select tilemap first palette*/
#define RPC_SELECT_TILEMAP_PALETTE_1  0b01110000 /* select tilemap second palette*/

#define REG_ENHANCED_ULA_PALETTE_EXTENSION  0x44 /* Enhanced Palette Data Register */

#define REG_TILEMAP_TRANSPARENCY_INDEX 0x4C /* Tilemap transparency index register */

#define TILE_PALETTE_SIZE_8_BIT 256 /* 256 bytes for 8-bit palette */
#define TILE_PALETTE_SIZE_9_BIT 512 /* 512 bytes for 9-bit palette */



/***************************************************
 * private function prototypes
 ***************************************************/
void init_zxnext_tilemap(void);
void init_zxnext_palette(void);

/***************************************************
 * private variables 
 ***************************************************/

 /**
 * @brief Tile palette data
 * 
 */
extern uint8_t tile_palette[]; 

void init_zxnext(void) 
{
    /* set CPU speed 28MHz */
    ZXN_WRITE_REG(REG_TURBO_MODE, RTM_28MHZ);

    /* disable RAM contention */
    ZXN_WRITE_REG(REG_PERIPHERAL_3, (ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION));

    /* Disable the ZXnext ULA screen */
    ZXN_WRITE_REG(REG_ULA_CONTROL, (ZXN_READ_REG(REG_ULA_CONTROL) | RUC_DISABLE_ULA_OUTPUT));

    /* Remove the ROM from MMU slots 0 and 1 by mapping in 8k bank 28 and 29 */
    /* This frees up 16k of memory at 0x0000 - 0x3FFF for our program */
    /* Map bank 28 into ZX Spectrum 8k MMU slot 0 */
    ZXN_WRITE_REG(0x50, PAGE_GLOBAL_STATE);
    /* Map bank 29 into ZX Spectrum 8k MMU slot 1 */
    ZXN_WRITE_REG(0x51, PAGE_GLOBAL_STATE_2);    

    init_zxnext_tilemap();

    init_zxnext_palette();
} 

void init_game_state(void)
{
    /* Init entity */
    entity_init();

    /* Init components */
    contained_init();
    container_init();
    creature_init();
    item_init();
    location_init();
    player_ctrl_init();
    renderable_init();
    timer_init();

    /* Init systems */
    system_event_init();
    system_player_init();
    system_timer_init();

    /* Init game */
    map_init();
}

void init_ui(void)
{
    g.msg_win.x = 0;
    g.msg_win.y = 24;
    g.msg_win.w = 40;
    g.msg_win.h = 8;
    g.msg_win.c_x = 0;
    g.msg_win.c_y = 0;
    g.msg_win.tile.tile_id = ' ';
    g.msg_win.tile.tile_attr = 0;

    g.stat_win.x = 30;
    g.stat_win.y = 0;
    g.stat_win.w = 10;
    g.stat_win.h = 24;
    g.stat_win.c_x = 0;
    g.stat_win.c_y = 0;
    g.stat_win.tile.tile_id = ' ';
    g.stat_win.tile.tile_attr = 0;

    g.main_win.x = 0;
    g.main_win.y = 0;
    g.main_win.w = 30;
    g.main_win.h = 24;
    g.main_win.c_x = 0;
    g.main_win.c_y = 0;
    g.main_win.tile.tile_id = ' ';
    g.main_win.tile.tile_attr = 0;    

    g.assert_win.x = 0;
    g.assert_win.y = 0;
    g.assert_win.w = 40;
    g.assert_win.h = 32;
    g.assert_win.c_x = 0;
    g.assert_win.c_y = 0;
    g.assert_win.tile.tile_id = ' ';
    g.assert_win.tile.tile_attr = 0;

    zxnext_tilemap_clear(&(g.msg_win.tile));
}

void init_zxnext_tilemap(void)
{
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

void init_zxnext_palette(void)
{
    /*
    * Select the tilemap palette 0 for writing
    *    0x43 Palette Control Register
    *    bit 7      set to disable auto-increment
    *    bits 6-4   select tilemap palette for writing/reading
    *    bit 3      select sprite palette (0 = palette 0, 1 = palette 1)
    *    bit 2      select layer 2 palette (0 = palette 0, 1 = palette 1)
    *    bit 1      select ULA palette (0 = palette 0, 1 = palette 1)
    *    bit 0      set to enable ULANext mode
    */ 
    ZXN_WRITE_REG(REG_PALETTE_CONTROL, RPC_SELECT_TILEMAP_PALETTE_0 );

    /*
     * Write 9-bit palette entries
     *  0x44 Palette Data Register
     *  bits 7-0   palette data bits 7-0
     *  bit 8      palette data bit 8
     */
    for (uint16_t i = 0 ; i < TILE_PALETTE_SIZE_9_BIT; i++)
    {
        ZXN_WRITE_REG(REG_ENHANCED_ULA_PALETTE_EXTENSION, tile_palette[i]);
    }

    // 0x4C Tilemap transparency index register
    ZXN_WRITE_REG(REG_TILEMAP_TRANSPARENCY_INDEX, 0b00000100);
}
