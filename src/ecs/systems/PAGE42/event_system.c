/**
 * @file event_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "event_system.h"

#include "ecs/entity.h"

#include "ecs/systems/systems_dispatch.h"

#include "core/ui.h"

/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void event_system_init(void)
{
}

void event_system_emit(const event_t event)
{
    ui_on_event(event);

    switch (event.type)
    {

        case EVENT_ATTACKED:
            break;
        case EVENT_BUMPED:
            break;
        case EVENT_CONSUMED:
            system_effect_handle_event(event);
            break;
        case EVENT_DAMAGED:
        case EVENT_DAMAGED_IMMUNE:
        case EVENT_DAMAGED_RESIST:
        case EVENT_DAMAGED_VULNERABLE:
        case EVENT_DIED:
        case EVENT_DROPPED:
        case EVENT_EQUIPPED:
        case EVENT_PICKED_UP:
        case EVENT_STOOD_ON:
        case EVENT_UNEQUIPPED:
            break;
        default:
            util_abort("Unknown event type");
    }
}
