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

#include "entity.h"
#include "timer_comp.h"

#include "player_system.h"

#include "../game/global_state.h"


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
    text_print_string(&g.msg_win, ".");
    for (uint8_t i = 0; i < g.timer_components.count; ) {
        entity_id_t e = g.timer_components.active_list[i];
        if (timer_tick(e))
        {
            if (entity_has_component(e, COMPONENT_PLAYER_CTRL))
            {
                player_system_update();
            }
            else if (entity_has_component(e, COMPONENT_AI_CTRL))
            {
                /* ai_system_update(e); */
            }
        }
        i++;
    }
 }
