/**
 * @file timer_comp.c
 * @author Paul Johnson
 * @brief Countdown timer, returns true when timer reaches zero and resets counter
 * 
 */

#include "timer_comp.h"

#include "timer_comp_priv.h"
#include "contained_comp.h"
#include "../entity.h"

#include "../../game/global_state.h"
#include "../../core/util.h"


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

bool_t timer_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_TIMER)); /* entity must not have timer component */

    g.timer_components.timers[entity].base_ticks = 0;
    g.timer_components.timers[entity].ticks = 0; 
    g.timer_components.timers[entity].active = 0; 

    g.timer_components.active_list[g.timer_components.count++] = entity;

    entity_set_component(entity, COMPONENT_TIMER); /* set entity timer component mask */

    return 1; /* success */
}

void timer_set(entity_id_t entity, uint8_t turns, uint8_t ticks)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_TIMER)); /* entity must have timer component */

    ticks = ticks + (turns * 10);

    g.timer_components.timers[entity].base_ticks = ticks;
    g.timer_components.timers[entity].ticks = ticks; 
    g.timer_components.timers[entity].active = 1; 
    
    return;
}

void timer_reset(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_TIMER)); /* entity must have timer component */

    g.timer_components.timers[entity].ticks = g.timer_components.timers[entity].base_ticks; 
    g.timer_components.timers[entity].active = 1; 
    
    return;
}

bool_t timer_tick(entity_id_t entity)
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
        /* timer reached zero*/
        timer_reset(entity);
        return 1;
    }
    return 0;
}

void timer_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    if (!entity_has_component(entity, COMPONENT_TIMER))
    {
        return;
    }
    g.timer_components.timers[entity].active = 0;

    for (uint8_t i = 0; i < g.timer_components.count; i++) {
        if (g.timer_components.active_list[i] == entity) {
            g.timer_components.active_list[i] = g.timer_components.active_list[--g.timer_components.count];
            break;
        }
    }    

    entity_clear_component(entity, COMPONENT_TIMER); /* clear entity timer component mask */
}