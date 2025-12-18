/**
 * @file effect_system.h
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EFFECT_SYSTEM_H
#define EFFECT_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/game.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void effect_system_apply_effects_by_source(entity_id_t target, entity_id_t source, effect_trigger_t trigger);

#endif // EFFECT_SYSTEM_H
