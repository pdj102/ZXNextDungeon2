/**
 * @file monster_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef MONSTER_SYSTEM_H
#define MONSTER_SYSTEM_H

#include "ecs/components/creature_comp.h"

#include "core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

void monster_system_init(void);

entity_id_t monster_system_create(creature_kind_t kind);
entity_id_t monster_system_create_player( void );

#endif // MONSTER_SYSTEM_H
