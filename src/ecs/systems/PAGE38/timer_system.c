/**
 * @file timer_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "timer_system.h"

#include <stdbool.h>

#include "ecs/entity.h"
#include "ecs/components/timer_comp.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 * ***************************************************/
static bool timer_system_tick(entity_id_t entity);


/***************************************************
 * public functions
 ***************************************************/
void timer_system_init(void)
{
    g.timer_components.count = 0;
}

void timer_system_update(void)
{
    /* Tick all timer components */
    for (uint8_t i = 0; i < g.timer_components.count; i++)
    {
        timer_system_tick(g.timer_components.list[i]);
    }
 }

 bool timer_system_has_fired(entity_id_t entity)
{
    return g.timer_components.timers[entity].fired;
}

void timer_system_reset(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_TIMER)); /* entity must have timer component */

    g.timer_components.timers[entity].ticks = g.timer_components.timers[entity].base_ticks; 
    g.timer_components.timers[entity].active = 1; 
    g.timer_components.timers[entity].fired = 0;
}

 /***************************************************
 * private functions
 ***************************************************/

static bool timer_system_tick(entity_id_t entity)
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

void timer_system_cleanup(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_component(entity, COMPONENT_TIMER))
    {
        return;
    }
    g.timer_components.timers[entity].active = 0;

    /* Remove from active timer list */
    for (uint8_t i = 0; i < g.timer_components.count; i++) {
        if (g.timer_components.list[i] == entity) {
            g.timer_components.list[i] = g.timer_components.list[--g.timer_components.count];
            break;
        }
    }    

    entity_clear_component(entity, COMPONENT_TIMER); /* clear entity timer component mask */
}