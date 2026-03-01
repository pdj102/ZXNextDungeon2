/**
 * @file ui.c
 * @author Paul  Johnson
 * @brief Game UI
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/ui.h"

#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */

#include "ecs/systems/PAGE42/event_system.h"

#include "game/PAGE68/ui_init.h"
#include "game/PAGE68/ui_msg.h"
#include "game/PAGE68/ui_stat.h"
#include "game/PAGE68/ui_main.h"

#include "game/global_state.h"

#include "game/memory_map.h"

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
static void ui_update_stats(void);

/***************************************************
 * functions
 ***************************************************/
void ui_init(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_init_b();

    ZXN_WRITE_MMU6(current_bank);

 }

void ui_on_event(const event_t *event)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_msg_win_on_event(event);
    ui_stat_win_on_event(event);
    ui_main_win_on_event(event);

    ZXN_WRITE_MMU6(current_bank);

 }

void ui_update(void)
{
    if (g.main_win.dirty == 1)
    {
        map_render();
        g.main_win.dirty = 0;
    }

    if (g.stat_win.dirty == 1)
    {
        ui_update_stats();
        g.stat_win.dirty = 0;
    }
}
/***************************************************
 * private functions
 ****************************************************/
static void ui_update_stats(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_stat_update();

    ZXN_WRITE_MMU6(current_bank);   
}