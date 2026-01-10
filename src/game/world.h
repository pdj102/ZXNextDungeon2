/**
 * @file world.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef world_H
#define world_H

#include "ecs/entity.h"
#include "ecs/systems/PAGE42/event_system.h"
#include "game/global_state.h"


#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/


/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void world_handle_event(const event_t *event);
void new_game(void);
void world_process_entity_destructions(void);
void world_destroy_non_persistent_entities(void);
void world_detach_persistent_entities(void);
void world_attach_entity(entity_id_t id, uint8_t x, uint8_t y);
void world_detach_entity(entity_id_t id);

#endif // world_H
