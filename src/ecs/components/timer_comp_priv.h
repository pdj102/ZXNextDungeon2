/**
 * @file timer_comp_priv.h
 * @brief Private/internal declarations for timer_comp.c
 *
 * This header exposes internal timer definitions only to files that need them
 * (primarily `timer_comp.c` and systems that operate on timers). It should NOT be included by general modules.
 */

#ifndef TIMER_COMP_PRIV_H
#define TIMER_COMP_PRIV_H

#include "ecs/entity.h"

#include "ecs/components/timer_comp.h" 

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

 /* timer component */
typedef struct {
    uint8_t base_ticks; /* reset period ticks */
    uint8_t ticks;      /* remaining ticks */
    bool_t  active;     /* true if counting down */
    bool_t  fired;      /* true if count down reached zero */
} timer_comp_t;

/* Timer components - fast iterate */
typedef struct {
    timer_comp_t timers[MAX_ENTITIES]; /* array of timers */
    uint8_t list[MAX_ENTITIES]; /* list of entities with timer component*/
    uint8_t count;
} timer_components_t;



#endif /* TIMER_COMP_PRIV_H */

