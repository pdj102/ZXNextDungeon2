/**
 * @file equip_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIP_COMP_H
#define EQUIP_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
  typedef enum {
    EQUIP_NONE = 0,
    EQUIP_HEAD,
    EQUIP_NECK,
    EQUIP_BODY,
    EQUIP_HANDS,
    EQUIP_FINGER_LEFT,
    EQUIP_FINGER_RIGHT,
    EQUIP_FEET,
    EQUIP_LEGS,
    EQUIP_MELEE,
    EQUIP_AMMO,
    EQUIP_RANGED,
    EQUIP_SHIELD,
    EQUIP_COUNT
} equip_slot_t;
 
 typedef entity_id_t equip_slots_t[EQUIP_COUNT];
 
/***************************************************
 * public function prototypes
 ***************************************************/
void player_init(void);
bool_t equip_add(entity_id_t entity);
void equip_remove(entity_id_t entity);

#endif // EQUIP_COMP_H
