/**
 * @file item_system.h
 * @author Paul Johnson
 * @brief Items are physical objects in game world.
 */

#ifndef ITEM_SYSTEM_H
#define ITEM_SYSTEM_H

#include "ecs/entity.h"
#include "core/text.h"


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
    ITEM_SHORT_BOW,
    // Armour
    ITEM_LEATHER_ARMOUR,
    // Shields
    ITEM_SHIELD,
    // Ammo
    ITEM_ARROW,
    ITEM_BOLT,
    ITEM_STONE,
    ITEM_DART,
    // Potions
    ITEM_POTION_OF_HEALING,
    // Scrolls
    // Food and drink
    ITEM_BREAD,
    ITEM_APPLE,
    // Rings
    ITEM_RING_OF_STRENGTH,
    // Wands
    // Light sources
    // Keys
    ITEM_KEY,
    // Quest items
    ITEM_AMULET,
    ITEM_KIND_COUNT
} item_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/

entity_id_t item_system_create(item_kind_t kind, uint8_t quantity);

#endif // ITEM_BASE_H
