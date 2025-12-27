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

#include "game/PAGE68/ui_msg.h"
#include "game/PAGE68/ui_stat.h"

#include "game/game.h"

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

void ui_on_event(const event_t event)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_msg_win_on_event(&event);
    ui_stat_win_on_event(&event);

    ZXN_WRITE_MMU6(current_bank);

 }

void ui_update_primary_stats(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_stat_update_primary_stats();

    ZXN_WRITE_MMU6(current_bank);   
}

void ui_update_secondary_stats(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_stat_update_secondary_stats();

    ZXN_WRITE_MMU6(current_bank);   
}

void ui_update_resource_stats(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();
    ZXN_WRITE_MMU6(PAGE_UI);

    ui_stat_update_resource_stats();

    ZXN_WRITE_MMU6(current_bank);   
}


    