/**
 * @file event_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "event_system.h"

#include "../entity.h"

#include "../../core/ui.h"

/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void event_system_init(void)
{
}

void event_emit(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val)
 {
    ui_on_event(type, src, tgt, val);
/*
    switch (e->type)
    {
        case EVENT_ATTACKED:
            ui_on_damage(e);
            sound_on_damage(e);
            log_on_damage(e);
            break;

        case EVENT_DIED:
            ui_on_death(e);
            sound_on_death(e);
            break;

        case EVENT_PICKED_UP:
            ui_on_item_pickup(e);
            log_on_item_pickup(e);
            break;

        default:
            break;
    }
*/
}
