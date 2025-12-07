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
    // Wearable
    ITEM_CLASS_HEAD,
    ITEM_CLASS_NECKLACE,
    ITEM_CLASS_ARMOUR,
    ITEM_CLASS_GLOVE,
    ITEM_CLASS_TROUSERS,
    ITEM_CLASS_RING,
    ITEM_CLASS_SHOES,
    // Melee weapons
    ITEM_CLASS_MELEE,
    // Ranged weapons
    ITEM_CLASS_RANGED,
    // Ammo
    ITEM_CLASS_ARROW,
    // Shields
    ITEM_CLASS_SHIELD,    
    // Potions
    ITEM_CLASS_POTION,
    // Consumable
    ITEM_CLASS_CONSUMABLE,
    // Keys
    ITEM_CLASS_KEY
} item_class_t;

 typedef enum {
    ITEM_NONE = 0,
    ITEM_CLUB,
    ITEM_SHORT_SWORD,
    ITEM_SHIELD,
    ITEM_LEATHER_ARMOUR,
    ITEM_POTION_OF_HEALING,
    ITEM_KEY,
    ITEM_KIND_COUNT
} item_kind_t;

/* Item class head*/
typedef struct {
    int8_t ac_mod;
} head_t;

/* Item class necklace*/
typedef struct {
    int8_t ac_mod;
} necklace_t;

/* Item class melee*/
typedef struct {
    attack_type_t attack_type;
    dice_roll_t damage_roll;
    damage_type_t damage_type;
    int8_t hit_mod;     /* to hit modifier */
    int8_t damage_mod;  /* to damage modifier */
} melee_t;

/* Item class ranged*/
typedef struct {
    attack_type_t attack_type;
    dice_roll_t damage_roll;
    damage_type_t damage_type;
    uint8_t range;
    int8_t hit_mod;     /* to hit modifier */
    int8_t damage_mod;  /* to damage modifier */
} ranged_t;



/* Item component data per entity */
typedef struct {
    item_class_t class;  /* type of item (e.g. weapon, armor, consumable) */
    item_kind_t kind;    /* index into item_comp_bases[] */
    uint8_t quantity;    /* stack size */
    union {
        head_t head;
        necklace_t necklace;
        melee_t melee;
        ranged_t ranged;
    } item_data;
} item_comp_t;


typedef item_comp_t item_components_t[MAX_ENTITIES]; /* item component data */

/***************************************************
 * public function prototypes
 ***************************************************/
void item_init(void);

uint8_t item_add(entity_id_t entity, item_kind_t type, uint8_t quantity);

void item_remove(entity_id_t entity);

#endif // ITEM_COMP_H
