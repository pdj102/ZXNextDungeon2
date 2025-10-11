/**
 * @file location_comp.h
 * @author Paul Johnson
 * @brief location management for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOCATION_COMP_H
#define LOCATION_COMP_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void location_init(void);
bool_t location_init_for_entity(entity_id_t entity);
void location_place_on_map(entity_id_t entity, uint8_t x, uint8_t y);
void location_place_in_container(entity_id_t entity, entity_id_t container);
void location_remove_from_map(entity_id_t entity);
void location_remove_from_container(entity_id_t entity);
void location_remove_from_current(entity_id_t entity);
void location_destroy(entity_id_t id);

#endif // LOCATION_COMP_H
