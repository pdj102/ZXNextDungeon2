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

#include "../entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    EVENT_NONE,
    EVENT_ENTITY_ATTACKED,
    EVENT_ENTITY_ATTACKED_MISSED,
    EVENT_ENTITY_DIED,
    EVENT_ITEM_PICKED_UP,
    EVENT_ITEM_DROPPED,
    EVENT_COUNT
} event_type_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void event_system_init(void);
void event_emit(event_type_t type, uint8_t src, uint8_t tgt, uint8_t val);

#endif // EVENT_SYSTEM_H
