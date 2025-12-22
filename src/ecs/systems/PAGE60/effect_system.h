/**
 * @file effect_system.h
 * @author Paul Johnson
 * @brief Effect system for ECS - public API
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EFFECT_SYSTEM_H
#define EFFECT_SYSTEM_H

#include <stdint.h>

#include "ecs/components/PAGE50/effect_comp.h"
#include "ecs/systems/PAGE42/event_system.h"

#include "ecs/entity.h"


/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
 /*
  * @brief Init the event system
  *   
  */
void effect_system_init(void );

 /*
  * @brief Handle events
  *   
  */
void effect_system_handle_event(const event_t event);

void effect_system_process_entity_turn(entity_id_t entity);

/*
 * @brief Cleanup effects when an entity is marked for destruction  
 * @details When the source is destroyed, all active effects referencing it should be cleaned up.
 * @param source The entity that is being destroyed
 */
void effect_system_cleanup_entity(entity_id_t source);

/*
 * @brief Returns the sum of all effect mods for a given attribute for an actor
 * @details This function calculates the total modifiers applied to a specific attribute by all active effects
 * @param actor The actor 
 */
int8_t effect_system_attribute_mod_sum(entity_id_t actor, effect_attribute_t attribute);


#endif // EFFECT_SYSTEM_H
