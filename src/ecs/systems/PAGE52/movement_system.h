/**
 * @file movement_system.h
 * @author Paul Johnson
 * @brief movement system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/spatial.h"

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
 void movement_system_init(void);
 void movement_system_place(entity_id_t entity, uint8_t x, uint8_t y);
 bool movement_system_try_move(entity_id_t actor, int8_t dx, int8_t dy);
 bool movement_system_try_move_random(entity_id_t actor);
 bool movement_system_try_move_towards(entity_id_t entity, coord_t *coord);
bool movement_system_location_equal(entity_id_t entity1, entity_id_t entity2);
bool movement_system_are_adjacent(entity_id_t entity1, entity_id_t entity2);
void movement_system_detach(entity_id_t entity);

#endif // MOVEMENT_SYSTEM_H
