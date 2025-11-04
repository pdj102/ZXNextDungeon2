/**
 * @file timer_comp.h
 * @author Paul Johnson
 * @brief Countdown timer, returns true when timer reaches zero and resets counter
 * 
 */

#ifndef TIMER_COMP_H
#define TIMER_COMP_H

#include <stdint.h>

#include "../entity.h"

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
bool_t timer_add(entity_id_t entity);
void timer_set(entity_id_t entity, uint8_t turns, uint8_t ticks);
bool_t timer_tick(entity_id_t entity);
void timer_remove(entity_id_t entity);

#endif // TIMER_COMP_H
