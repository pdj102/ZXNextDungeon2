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
#include "ecs/components/PAGE50/effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "game/game.h"

/***************************************************
 * public types
 ***************************************************/
typedef struct
{
    entity_id_t     source;   /* Entity providing the effect (item, weapon, trap, aura, etc.) */
    entity_id_t     target;   /* Entity receiving the effect */
    effect_trigger_t trigger; /* Why the effect is being applied (consumed, hit, equipped, etc.) */
} effect_apply_t;

/***************************************************
 * public function prototypes
 ***************************************************/

 /*
  * @brief Pass event to effect system for processing 
  *   
  */
void effect_system_handle_event(const event_t event);

#endif // EFFECT_SYSTEM_H
