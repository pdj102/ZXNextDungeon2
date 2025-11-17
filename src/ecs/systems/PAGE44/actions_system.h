/**
 * @file actions_system.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ACTIONS_SYSTEM_H
#define ACTIONS_SYSTEM_H

#include <stdint.h>
#include <sys/types.h>

#include "../../entity.h"

#include "../../../core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

bool_t actions_system_try_melee_attack(entity_id_t creature, entity_id_t target);
bool_t actions_system_try_pickup(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_drop(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_quaff(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_eat(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_equip(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_unequip(entity_id_t creature, entity_id_t item);
bool_t actions_system_try_open(entity_id_t creature, entity_id_t feature);
bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature);
int8_t actions_system_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type);
bool_t actions_system_try_die(entity_id_t creature);
bool_t actions_system_try_move(entity_id_t entity, int8_t dx, int8_t dy);

#endif // ACTIONS_SYSTEM_H
