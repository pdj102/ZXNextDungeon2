/**
 * @file event_system.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    EVENT_NONE,
    EVENT_ATTACKED,
    EVENT_ATTACKED_MISSED,
    EVENT_BUMPED,
    EVENT_STOOD_ON,
    EVENT_DIED,
    EVENT_PICKED_UP,
    EVENT_DROPPED,
    EVENT_EQUIPPED,
    EVENT_UNEQUIPPED,
    EVENT_COUNT
} event_type_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void event_system_init(void);

/*
 * @brief Emits an event to the system.
 * @param type The type of event to emit.
 * @param src The source entity ID e.g. the entity that caused / initiated the event
 * @param tgt The target entity ID e.g. the entity that was affected / acted upon by the event
 * @param val Optional value associated with the event e.g. damage dealt
 * 
 * @example  event_emit(EVENT_ATTACKED, PLAYER, RAT, 50); Player attacked the rat  

 */
void event_system_emit(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val);

#endif // EVENT_SYSTEM_H
