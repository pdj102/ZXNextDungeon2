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
    EVENT_ATTACKED,                 // Source attacked target
    EVENT_ATTACKED_AND_CRITICAL,    // Source attacked target and critical hit
    EVENT_ATTACKED_AND_MISSED,      // Source attacked target and missed
    EVENT_BUMPED,                   // Source bumped target
    EVENT_STOOD_ON,                 // Source stood on target
    EVENT_DIED,                     // source died, target = ENTITY_ID_INVALID
    EVENT_PICKED_UP,                // Source picked up target
    EVENT_DROPPED,                  // Source dropped target
    EVENT_EQUIPPED,                 // Source equipped target
    EVENT_UNEQUIPPED,               // Source unequipped target
    EVENT_DAMAGED,                  // source damaged target
    EVENT_DAMAGED_IMMUNE,           // source attempted to damage target; target immune
    EVENT_DAMAGED_RESIST,           // source damaged target; target resisted
    EVENT_DAMAGED_VULNERABLE,       // source damaged target; target vulnerable
    EVENT_CONSUMED,                 // Source consumed target
    EVENT_HEALED_HP,                // Source healed target HP
    EVENT_HEALED_MP,                // Source healed target MP
    EVENT_ACTIVE_EFFECT_ATTACHED,   // Source (entity_id_invalid if no specific source) applied an active effect to target
    EVENT_ACTIVE_EFFECT_UNATTACHED, // Source (entity_id_invalid if no specific source) removed an effect from target
    EVENT_ACTIVE_EFFECT_EXPIRED,    // Source's (entity_id_invalid if no specific source) effect expired on target
    EVENT_SPOTTED_TARGET,           // Source spotted target
    EVENT_COUNT

} event_type_t;

typedef struct {
    event_type_t    type;   /* The type of event to emit */
    entity_id_t     source; /* The entity that caused / initiated the event */
    entity_id_t     target; /* The entity that the action applied to / was affected */
    uint8_t         value;  /* Optional value associated with the event */
} event_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void event_system_init(void);

/*
 * @brief Emit an event to all systems that are interested in it.
 */
void event_system_emit(const event_t *event);

#endif // EVENT_SYSTEM_H
