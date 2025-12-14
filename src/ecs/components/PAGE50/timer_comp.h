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

#include "game/game.h"

#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
 /* timer component */
typedef struct {
    ticks_t base_ticks; /* reset period ticks */
    ticks_t ticks;      /* remaining ticks */
    bool_t  active;     /* true if counting down */
    bool_t  fired;      /* true if count down reached zero */
} timer_comp_t;

/* Timer components - fast iterate */
typedef struct {
    timer_comp_t timers[MAX_ENTITIES]; /* array of timers */
    uint8_t list[MAX_ENTITIES]; /* list of entities with timer component*/
    uint8_t count;
} timer_components_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void timer_init(void);
void timer_add(entity_id_t entity, ticks_t ticks);
void timer_remove(entity_id_t entity);
void timer_set(entity_id_t entity, ticks_t ticks);
bool_t timer_has_fired(entity_id_t entity);
void timer_reset(entity_id_t entity);

#endif // TIMER_COMP_H
