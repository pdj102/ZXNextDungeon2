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

#include "../../entity.h"
#include "../../components/timer_comp.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 * ***************************************************/
bool_t timer_system_tick(entity_id_t entity);


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
        timer_system_tick(g.timer_components.list[i]);
    }
 }

 /***************************************************
 * private functions
 ***************************************************/

bool_t timer_system_tick(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_TIMER)); /* entity must have timer component */
    
    if ( g.timer_components.timers[entity].active == 0)
    {
        return 0;
    }

    if (g.timer_components.timers[entity].ticks > 0)
    {
        g.timer_components.timers[entity].ticks--;
    }

    if (g.timer_components.timers[entity].ticks == 0)
    {
        /* one shot timer reached zero */
        /* to implement a repeating timer would need to reset */
        g.timer_components.timers[entity].active = 0;
        g.timer_components.timers[entity].fired = 1;
        return 1;
    }
    return 0;
}

