/**
 * @file container_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef CONTAINER_SYSTEM_H
#define CONTAINER_SYSTEM_H

#include <stdbool.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void container_system_init(void);
bool container_system_try_pickup(entity_id_t actor, entity_id_t item);
bool container_system_try_drop(entity_id_t actor, entity_id_t item);
void container_system_add(entity_id_t container, entity_id_t item);
void container_system_remove(entity_id_t item);
uint8_t container_system_count(entity_id_t container);
entity_id_t container_system_get_first(entity_id_t container);
entity_id_t container_system_get_next(entity_id_t entity);
entity_id_t container_system_get_at(entity_id_t container, uint8_t index);
void container_system_mark_contents_for_destruction(entity_id_t container);
void container_system_clean_up(entity_id_t id);

#endif // CONTAINER_SYSTEM_H
