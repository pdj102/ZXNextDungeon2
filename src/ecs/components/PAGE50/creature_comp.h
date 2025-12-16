/**
 * @file creature_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CREATURE_COMP_H
#define CREATURE_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "core/text.h"
#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    CREATURE_CLASS_NONE = 0,
    CREATURE_CLASS_ABERRATIONS,
    CREATURE_CLASS_BEASTS,
    CREATURE_CLASS_CELESTIALS,
    CREATURE_CLASS_CONSTRUCTS,
    CREATURE_CLASS_DRAGONS,
    CREATURE_CLASS_ELEMENTALS,
    CREATURE_CLASS_FEY,
    CREATURE_CLASS_FIENDS,
    CREATURE_CLASS_GIANTS,
    CREATURE_CLASS_HUMANOIDS,
    CREATURE_CLASS_MONSTROSITIES,
    CREATURE_CLASS_OOZES,
    CREATURE_CLASS_PLANTS,
    CREATURE_CLASS_UNDEAD
} creature_class_t;

typedef enum creature_kind_e {
    CREATURE_NONE = 0,
   /* CREATURE_CLASS_ABERRATIONS */
   /* CREATURE_CLASS_BEASTS */    
    CREATURE_RAT,
   /* CREATURE_CLASS_CELESTIALS */
   /* CREATURE_CLASS_CONSTRUCTS */
   /* CREATURE_CLASS_DRAGONS */
   /* CREATURE_CLASS_ELEMENTALS */
   /* CREATURE_CLASS_FEY */
   /* CREATURE_CLASS_FIENDS */
   /* CREATURE_CLASS_GIANTS */
   /* CREATURE_CLASS_HUMANOIDS */    
    CREATURE_COMMONER,
    CREATURE_PLAYER,
    /* CREATURE_CLASS_MONSTROSITIES */
    /* CREATURE_CLASS_OOZES */
    /* CREATURE_CLASS_PLANTS */    
    CREATURE_WITHERWEED, 
    CREATURE_KIND_COUNT
} creature_kind_t;

typedef enum creature_status_e {
    CREATURE_STATUS_NONE,
    CREATURE_STATUS_ALIVE,
    CREATURE_STATUS_DEAD
} creature_status_t;

typedef struct {
    creature_kind_t kind;   /* index into creature_comp_bases[] */
    creature_status_t status;      
} creature_comp_t;

typedef creature_comp_t creature_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t creature_add(entity_id_t entity, creature_kind_t kind);

void creature_remove(entity_id_t entity);

#endif // CREATURE_COMP_H
