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
    CREATURE_STATUS_DEAD,
    CREATURE_STATUS_WON
} creature_status_t;

typedef enum creature_cr_e {
    CREATURE_CR_NONE,
    CREATURE_CR_0,
    CREATURE_CR_1_8,    // 1/8 or less
    CREATURE_CR_1_4,    // 1/4 or less
    CREATURE_CR_1_2,    // 1/2 or less
    CREATURE_CR_1,
    CREATURE_CR_2,
    CREATURE_CR_3,
    CREATURE_CR_4,
    CREATURE_CR_5,
    CREATURE_CR_6,
    CREATURE_CR_7,
    CREATURE_CR_8
} creature_cr_t;

typedef struct {
    // creature_kind_t kind;   /* TODO remove index into creature_comp_bases[] */
    creature_status_t status;
    creature_cr_t challenge; 
} creature_comp_t;

typedef creature_comp_t creature_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/


#endif // CREATURE_COMP_H
