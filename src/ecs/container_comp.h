/**
 * @file container_comp.h
 * @author Paul Johnson
 * @brief 
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
bool_t container_add(entity_id_t entity);
void container_remove(entity_id_t entity);

bool_t container_add_entity(entity_id_t container, entity_id_t entity);
void container_remove_entity(entity_id_t entity);
void container_destroy_contents(entity_id_t id);

#endif // CONTAINER_COMP_H
