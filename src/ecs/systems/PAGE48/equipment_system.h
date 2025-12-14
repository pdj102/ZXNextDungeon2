/**
 * @file equipment_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef EQUIPMENT_SYSTEM_H
#define EQUIPMENT_SYSTEM_H

#include <sys\types.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void equipment_system_init(void);
bool_t actions_system_try_equip(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_unequip(entity_id_t creature, entity_id_t item);

void equipment_system_clean_up(entity_id_t id);

#endif // EQUIPMENT_SYSTEM_H
