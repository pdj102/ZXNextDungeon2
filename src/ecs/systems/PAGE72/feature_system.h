/**
 * @file feature_system.h
 * @author Paul Johnson
 * @brief Items are physical objects in game world.
 */

#ifndef FEATURE_SYSTEM_H
#define FEATURE_SYSTEM_H

#include "ecs/entity.h"
#include "core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

 typedef enum {
    FEATURE_NONE = 0,
    // Doors
    FEATURE_CLOSED_DOOR,
    FEATURE_OPEN_DOOR,
    // Containers & Storage
    FEATURE_CHEST,
    // Alters
    // Mechanisms (levers, switches, )
    // Traps (hidden)
    // Statues
    // Stairs
    FEATURE_DOWN_STAIRS,
    FEATURE_UP_STAIRS,
    // Hazards
    FEATURE_KIND_COUNT
} feature_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/

entity_id_t feature_system_create(feature_kind_t kind);

#endif // FEATURE_SYSTEM_H
