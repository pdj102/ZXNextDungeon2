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
    trigger_flag_t  trigger;  /* Trigger that caused the effect (attack, damage, etc.) */
} trigger_context_t;

/***************************************************
 * public function prototypes
 ***************************************************/
 /*
  * @brief Pass event to effect system for processing 
  *   
  */
void effect_system_init(void );

 /*
  * @brief Pass event to effect system for processing 
  *   
  */
void effect_system_handle_event(const event_t event);

/*
 * @brief Removes active effects from all entities where the source entity is source
 * @details Call this function in the cleanup phase when the source entity is marked for destruction to ensure no dangling source references in active effects 
 * @param source The source entity whose active effects need to be removed
 */
void effect_system_cleanup_entity(entity_id_t source);


#endif // EFFECT_SYSTEM_H
