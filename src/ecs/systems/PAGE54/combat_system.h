/**
 * @file combat_system.h
 * @author Paul Johnson
 * @brief combat system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    ATTACK_MISS,
    ATTACK_HIT,
    ATTACK_CRITICAL
} attack_result_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void combat_system_init(void);
bool combat_system_try_melee_attack(entity_id_t creature, entity_id_t target);

#endif // COMBAT_SYSTEM_H
