/**
 * @file equipable_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIPABLE_COMP_H
#define EQUIPABLE_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    EQUIPABLE_NONE = 0,
    // Wearable
    EQUIPABLE_HEAD,
    EQUIPABLE_NECK,
    EQUIPABLE_BODY,
    EQUIPABLE_HANDS,
    EQUIPABLE_LEGS,
    EQUIPABLE_FINGER,
    EQUIPABLE_FEET,
    // Melee weapons
    EQUIPABLE_MELEE,
    // Ranged weapons
    EQUIPABLE_RANGED,
    // Ammo
    EQUIPABLE_AMMO,
    // Shields
    EQUIPABLE_SHIELD,
    EQUIPABLE_COUNT
} equipable_slot_t;

typedef struct {
    equipable_slot_t slot;
    entity_id_t equipped_by;
} equipable_comp_t;

typedef equipable_comp_t equipable_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/
void equipable_init(void);

uint8_t equipable_add(entity_id_t entity, equipable_slot_t type);

void equipable_remove(entity_id_t entity);

#endif // EQUIPABLE_COMP_H
