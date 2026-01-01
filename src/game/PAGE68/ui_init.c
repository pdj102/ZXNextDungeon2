/**
 * @file ui_init.c
 * @author Paul  Johnson
 * @brief Game UI_INIT
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/PAGE68/ui_init.h"

#include "core/zxnext.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

 

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/
void ui_init_b(void)
{
    g.msg_win.x = 0;
    g.msg_win.y = 24;
    g.msg_win.w = 40;
    g.msg_win.h = 8;
    g.msg_win.c_x = 0;
    g.msg_win.c_y = 0;
    g.msg_win.dirty = 0;
    g.msg_win.tile.tile_id = ' ';
    g.msg_win.tile.tile_attr = PALETTE_WHITE;

    g.stat_win.x = 30;
    g.stat_win.y = 0;
    g.stat_win.w = 10;
    g.stat_win.h = 24;
    g.stat_win.c_x = 0;
    g.stat_win.c_y = 0;
    g.stat_win.dirty = 0;
    g.stat_win.tile.tile_id = ' ';
    g.stat_win.tile.tile_attr = PALETTE_WHITE;

    g.main_win.x = 0;
    g.main_win.y = 0;
    g.main_win.w = 30;
    g.main_win.h = 24;
    g.main_win.c_x = 0;
    g.main_win.c_y = 0;
    g.main_win.dirty = 0;
    g.main_win.tile.tile_id = ' ';
    g.main_win.tile.tile_attr = PALETTE_WHITE;

    g.assert_win.x = 0;
    g.assert_win.y = 0;
    g.assert_win.w = 40;
    g.assert_win.h = 32;
    g.assert_win.c_x = 0;
    g.assert_win.c_y = 0;
    g.assert_win.dirty = 0;
    g.assert_win.tile.tile_id = ' ';
    g.assert_win.tile.tile_attr = PALETTE_RED;

    zxnext_tilemap_clear(&(g.msg_win.tile));
}