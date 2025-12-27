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

#include "game/ui.h"

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
    system_effect_handle_event(event);
    ui_on_event(event);
}
