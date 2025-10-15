/**
 * @file contained_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CONTAINED_COMP_H
#define CONTAINED_COMP_H

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
void contained_init(void);
bool_t contained_init_for_entity(entity_id_t entity);
void contained_add(entity_id_t container, entity_id_t entity);
void contained_remove(entity_id_t entity);
void contained_destroy(entity_id_t id);

#endif // CONTAINED_COMP_H
