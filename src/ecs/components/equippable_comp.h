/**
 * @file equippable_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIPPABLE_COMP_H
#define EQUIPPABLE_COMP_H

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
    EQUIPPABLE_NONE = 0,
    // Wearable
    EQUIPPABLE_HEAD,
    EQUIPPABLE_NECK,
    EQUIPPABLE_BODY,
    EQUIPPABLE_HANDS,
    EQUIPPABLE_LEGS,
    EQUIPPABLE_FINGER,
    EQUIPPABLE_FEET,
    // Melee weapons
    EQUIPPABLE_MELEE,
    // Ranged weapons
    EQUIPPABLE_RANGED,
    // Ammo
    EQUIPPABLE_AMMO,
    // Shields
    EQUIPPABLE_SHIELD,
    EQUIPPABLE_COUNT
} equippable_slot_t;

typedef struct {
    equippable_slot_t slot;
} equippable_comp_t;

typedef equippable_comp_t equippable_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/
void equippable_init(void);

uint8_t equippable_add(entity_id_t entity, equippable_slot_t type);

void equippable_remove(entity_id_t entity);

#endif // EQUIPPABLE_COMP_H
