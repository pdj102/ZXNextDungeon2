/**
 * @file timer_comp.c
 * @author Paul Johnson
 * @brief Countdown timer, returns true when timer reaches zero and resets counter
 * 
 */

#include "ecs/components/PAGE50/timer_comp.h"

#include "ecs/components/PAGE50/contained_comp.h"
#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void timer_init(void)
{
    g.timer_components.count = 0;
}

void timer_add(entity_id_t entity, ticks_t ticks)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_TIMER)); /* entity must not have timer component */

    /* Set timer */
    g.timer_components.timers[entity].base_ticks = ticks;
    g.timer_components.timers[entity].ticks = ticks; 
    g.timer_components.timers[entity].active = 1;
    g.timer_components.timers[entity].fired = 0;

    /* Add to active timer list*/
    g.timer_components.list[g.timer_components.count++] = entity;

    entity_set_component(entity, COMPONENT_TIMER); /* set entity timer component mask */
}

void timer_remove(entity_id_t entity)
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

