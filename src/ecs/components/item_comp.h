/**
 * @file item_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ITEM_COMP_H
#define ITEM_COMP_H

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
    ITEM_CLASS_NONE = 0,

    // Melee weapons
    ITEM_CLASS_MELEE,
    // Ranged weapons
    ITEM_CLASS_RANGED,
    // Armour
    ITEM_CLASS_ARMOUR,
    // Shields
    ITEM_CLASS_SHIELD,
    // Ammo
    ITEM_CLASS_AMMO,
    // Potions
    ITEM_CLASS_POTION,    
    // Scrolls
    ITEM_CLASS_SCROLL,
    // Food and drink
    ITEM_CLASS_CONSUMABLE,
    // Rings
    ITEM_CLASS_HELMET,
    ITEM_CLASS_NECKLACE,
    ITEM_CLASS_GLOVE,
    ITEM_CLASS_TROUSERS,
    ITEM_CLASS_RING,
    ITEM_CLASS_SHOES,
    // Wands
    ITEM_CLASS_WAND,
    // Light sources
    ITEM_CLASS_LIGHT,
    // Keys
    ITEM_CLASS_KEY
} item_class_t;

 typedef enum {
    ITEM_NONE = 0,
    // Melee weapons
    ITEM_CLUB,
    ITEM_SHORT_SWORD,
    // Ranged weapons
    // Armour
    ITEM_LEATHER_ARMOUR,
    // Shields
    ITEM_SHIELD,
    // Ammo
    // Potions
    ITEM_POTION_OF_HEALING,
    // Scrolls
    // Food and drink
    ITEM_BREAD,
    // Rings
    ITEM_RING_OF_STRENGTH,
    // Wands
    // Light sources
    // Keys    
    ITEM_KEY,
    ITEM_KIND_COUNT
} item_kind_t;

/* Item component data per entity */
typedef struct {
    item_kind_t kind;    /* index into item_comp_bases[] */
    uint8_t quantity;    /* stack size */
} item_comp_t;

typedef item_comp_t item_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // ITEM_COMP_H
