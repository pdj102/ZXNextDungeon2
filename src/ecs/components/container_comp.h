/**
 * @file container_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef CONTAINER_COMP_H
#define CONTAINER_COMP_H

#include <stdint.h>

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
void container_init(void);
bool_t container_add(entity_id_t entity);
entity_id_t container_get_first(entity_id_t container);
uint8_t container_count(entity_id_t container);
void container_remove(entity_id_t entity);

#endif // CONTAINER_COMP_H
