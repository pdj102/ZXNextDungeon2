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
    EVENT_ATTACKED_AND_CRITICAL,
    EVENT_ATTACKED_AND_MISSED,
    EVENT_BUMPED,
    EVENT_STOOD_ON,
    EVENT_DIED,
    EVENT_PICKED_UP,
    EVENT_DROPPED,
    EVENT_EQUIPPED,
    EVENT_UNEQUIPPED,
    EVENT_DAMAGED,
    EVENT_DAMAGED_IMMUNE,
    EVENT_DAMAGED_RESIST,
    EVENT_DAMAGED_VULNERABLE,
    EVENT_CONSUMED,
    EVENT_HEALED_HP,
    EVENT_HEALED_MP,
    EVENT_ACTIVE_EFFECT_ATTACHED,
    EVENT_ACTIVE_EFFECT_UNATTACHED,
    EVENT_ACTIVE_EFFECT_EXPIRED,
    EVENT_COUNT
} event_type_t;

typedef struct {
    event_type_t    type;   /* The type of event to emit */
    entity_id_t     source; /* The entity that caused / initiated the event */
    entity_id_t     target; /* The entity that was affected */
    uint8_t         value;  /* Optional value associated with the event */
} event_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void event_system_init(void);

/*
 * @brief Emit an event to all systems that are interested in it.
 */
void event_system_emit(const event_t event);

#endif // EVENT_SYSTEM_H
