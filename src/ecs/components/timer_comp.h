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


/***************************************************
 * public function prototypes
 ***************************************************/
void timer_init(void);
bool_t timer_add(entity_id_t entity, ticks_t ticks);
void timer_remove(entity_id_t entity);
void timer_set(entity_id_t entity, ticks_t ticks);
bool_t timer_has_fired(entity_id_t entity);
void timer_reset(entity_id_t entity);

#endif // TIMER_COMP_H
