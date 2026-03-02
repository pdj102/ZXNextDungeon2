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
    g.msg_win.h = 7;
    g.msg_win.c_x = 0;
    g.msg_win.c_y = 0;
    g.msg_win.dirty = 0;
    g.msg_win.tile.tile_id = ' ';
    g.msg_win.tile.tile_attr = PALETTE_WHITE;

    g.info_win.x = 0;
    g.info_win.y = 31;
    g.info_win.w = 40;
    g.info_win.h = 1;
    g.info_win.c_x = 0;
    g.info_win.c_y = 0;
    g.info_win.dirty = 0;
    g.info_win.tile.tile_id = ' ';
    g.info_win.tile.tile_attr = PALETTE_WHITE;

    g.stat_win.x = 30;
    g.stat_win.y = 0;
    g.stat_win.w = 10;
    g.stat_win.h = 24;
    g.stat_win.c_x = 0;
    g.stat_win.c_y = 0;
    g.stat_win.dirty = 0;
    g.stat_win.tile.tile_id = ' ';
    g.stat_win.tile.tile_attr = PALETTE_WHITE;

    g.map_win.x = 0;
    g.map_win.y = 0;
    g.map_win.w = 30;
    g.map_win.h = 24;
    g.map_win.c_x = 0;
    g.map_win.c_y = 0;
    g.map_win.dirty = 0;
    g.map_win.tile.tile_id = ' ';
    g.map_win.tile.tile_attr = PALETTE_WHITE;

    g.main_win.x = 0;
    g.main_win.y = 0;
    g.main_win.w = 40;
    g.main_win.h = 32;
    g.main_win.c_x = 0;
    g.main_win.c_y = 0;
    g.main_win.dirty = 0;
    g.main_win.tile.tile_id = ' ';
    g.main_win.tile.tile_attr = PALETTE_WHITE;

    zxnext_tilemap_clear(&(g.msg_win.tile));
}