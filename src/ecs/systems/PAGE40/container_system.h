/**
 * @file container_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef CONTAINER_SYSTEM_H
#define CONTAINER_SYSTEM_H

#include <sys\types.h>

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
bool_t container_system_place_item_in(entity_id_t container, entity_id_t item);
void container_system_remove_item_from(entity_id_t container, entity_id_t item);
uint8_t container_system_count(entity_id_t container);
entity_id_t container_system_get_first(entity_id_t container);
entity_id_t container_system_get_next(entity_id_t entity);
entity_id_t container_system_get_at(entity_id_t container, uint8_t position);
void container_system_mark_contents_for_destruction(entity_id_t container);
void container_system_clean_up(void);

#endif // CONTAINER_SYSTEM_H
