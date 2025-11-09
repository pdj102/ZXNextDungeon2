/**
 * @file timer_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "timer_system.h"

#include <sys\types.h>

#include "../entity.h"
#include "../components/timer_comp.h"

#include "player_system.h"

#include "../../game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void timer_system_init(void)
{
}

void timer_system_update(void)
{
    /* Tick all timer components */
    for (uint8_t i = 0; i < g.timer_components.count; i++)
    {
        timer_tick(g.timer_components.list[i]);
    }
 }
