/**
 * @file container_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONTAINER_COMP_H
#define CONTAINER_COMP_H

#include <stdint.h>

#include "entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void container_init(void);
bool_t container_init_for_entity(entity_id_t entity);
void container_add(entity_id_t container, entity_id_t entity);
void container_remove(entity_id_t container, entity_id_t entity);
void container_destroy(entity_id_t id);

#endif // CONTAINER_COMP_H
