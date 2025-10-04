/**
 * @file name_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef NAME_COMP_H
#define NAME_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

#include "core/text.h"

/***************************************************
 * public defines
 ***************************************************/
 typedef enum {
    NAME_NONE = 0, 
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    NAME_RAT, 
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    NAME_COMMONER,
    NAME_PLAYER,
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    NAME_WITHERWEED,
    /* MONSTER_CLASS_UNDEAD */

    /* Melee weapons */
    NAME_CLUB,
    NAME_SHORT_SWORD,
    /* Ranged weapons*/
    /* Armour */    
    NAME_LEATHER_ARMOUR,
    /* Shields */
    NAME_SHIELD,
    /* Ammo */
    /* Potions */    
    NAME_POTION_OF_HEALING,
    /* Scrolls */
    /* Food and drink */
    NAME_BREAD,
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    NAME_KEY, 

    NAME_COUNT
} name_id_t;

/***************************************************
 * public types
 ***************************************************/
typedef uint8_t name_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/
void name_add(entity_id_t entity, name_id_t name);

void name_remove(entity_id_t entity);

#endif // NAME_COMP_H
