/**
 * @file slots_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef SLOTS_COMP_H
#define SLOTS_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
  typedef enum {
    SLOT_NONE = 0,
    SLOT_HEAD,
    SLOT_NECK,
    SLOT_BODY,
    SLOT_HANDS,
    SLOT_FINGER_LEFT,
    SLOT_FINGER_RIGHT,
    SLOT_FEET,
    SLOT_LEGS,
    SLOT_MELEE,
    SLOT_AMMO,
    SLOT_RANGED,
    SLOT_SHIELD,
    SLOT_COUNT
} slot_t;
 
 typedef entity_id_t slots_t[SLOT_COUNT];
 
/***************************************************
 * public function prototypes
 ***************************************************/
void slots_add(entity_id_t entity);
void slots_remove(entity_id_t entity);

#endif // SLOTS_COMP_H
