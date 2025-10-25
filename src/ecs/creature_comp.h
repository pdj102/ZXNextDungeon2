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

#include "entity.h"

#include "../core/text.h"
#include "../core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
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
    /* CREATURE_CLASS_MONSTROSITIES */
    /* CREATURE_CLASS_OOZES */
    /* CREATURE_CLASS_PLANTS */    
    CREATURE_WITHERWEED, 
    CREATURE_KIND_COUNT
} creature_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t creature_add(entity_id_t entity, creature_kind_t type);

void creature_get_tile(entity_id_t id, zxnext_tile_t *tile);

void creature_print_name(text_window_t *win, entity_id_t id);

void creature_remove(entity_id_t entity);

#endif // CREATURE_COMP_H
