/**
 * @file timer_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef TIMER_SYSTEM_H
#define TIMER_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void timer_system_init(void);
void timer_system_update(void);
bool timer_system_has_fired(entity_id_t entity);
void timer_system_reset(entity_id_t entity);
void timer_system_start(entity_id_t entity);
void timer_system_stop(entity_id_t entity);
void timer_system_cleanup(entity_id_t entity);

#endif // TIMER_SYSTEM_H
