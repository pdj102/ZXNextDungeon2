/**
 * @file ui_stat.c
 * @author Paul  Johnson
 * @brief Game UI_STAT
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/PAGE68/ui_main.h"

#include "ecs/components/components.h"
#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"

#include "core/text.h"

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
 * Public functions
 ***************************************************/
void ui_main_win_on_event(event_t *event)
{
 switch( event->type )
    {
        case EVENT_NONE:
            break;
        /* Events that require the game world map to be redrawn*/
        case EVENT_OPENED:
        case EVENT_CLOSED:
        case EVENT_DROPPED:
        case EVENT_PICKED_UP:
        case EVENT_DIED:
            g.main_win.dirty = 1;
            break;
    } 
}

void ui_main_update(void)
{

}

/***************************************************
 * Private functions
 ***************************************************/
