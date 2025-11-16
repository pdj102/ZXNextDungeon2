/**
 * @file container_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef CONTAINER_SYSTEM_H
#define CONTAINER_SYSTEM_H

#include <sys\types.h>

#include "../entity.h"

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
bool_t container_place_item_in_container(entity_id_t container, entity_id_t item);
void container_remove_item_from_container(entity_id_t container, entity_id_t item);
entity_id_t container_get_first(entity_id_t container);
entity_id_t container_get_next(entity_id_t entity);
uint8_t container_count(entity_id_t container);
void container_mark_contents_for_destruction(entity_id_t container);
void container_system_clean_up(void);

#endif // CONTAINER_SYSTEM_H
