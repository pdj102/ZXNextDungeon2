/**
 * @file location.h
 * @author Paul Johnson
 * @brief location management for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void place_on_map(entity_id_t entity, uint8_t x, uint8_t y);
void place_in_container(entity_id_t entity, entity_id_t container);
void remove_from_map(entity_id_t entity);
void remove_from_container(entity_id_t entity);
void remove_from_current_location(entity_id_t entity);

#endif // LOCATION_H
