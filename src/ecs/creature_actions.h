/**
 * @file creature_actions.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CREATURE_ACTIONS_H
#define CREATURE_ACTIONS_H

#include <stdint.h>
#include <sys/types.h>

#include "entity.h"

#include "../core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

bool_t creature_actions_try_melee_attack(entity_id_t creature, entity_id_t target);
bool_t creature_actions_try_pickup(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_drop(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_quaff(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_eat(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_equip(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_unequip(entity_id_t creature, entity_id_t item);
bool_t creature_actions_try_open(entity_id_t creature, entity_id_t feature);
bool_t creature_actions_try_close(entity_id_t creature, entity_id_t feature);
int8_t creature_actions_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type);
bool_t creature_actions_try_die(entity_id_t creature);

#endif // CREATURE_ACTIONS_H
