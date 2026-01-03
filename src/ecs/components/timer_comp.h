/**
 * @file timer_comp.h
 * @author Paul Johnson
 * @brief Countdown timer, returns true when timer reaches zero and resets counter
 * 
 */

#ifndef TIMER_COMP_H
#define TIMER_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
 
 typedef uint8_t ticks_t;
 
 /* timer component */
typedef struct {
    ticks_t base_ticks; /* reset period ticks */
    ticks_t ticks;      /* remaining ticks */
    bool  active;     /* true if counting down */
    bool  fired;      /* true if count down reached zero */
} timer_comp_t;

/* Timer components - fast iterate */
typedef struct {
    timer_comp_t timers[MAX_ENTITIES];  /* array of timers */
    uint8_t list[MAX_ENTITIES];         /* list of entities with timer component*/
    uint8_t count;
} timer_components_t;

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // TIMER_COMP_H
