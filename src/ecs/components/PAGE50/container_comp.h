/**
 * @file container_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef CONTAINER_COMP_H
#define CONTAINER_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Container component data per entity */
typedef struct {
    entity_id_t head;   /* Linked list head for entities within container */
    uint8_t capacity;   /* Maximum number of entities in the container */
    uint8_t count;      /* Current count of entities in the container */
} container_comp_t;

typedef container_comp_t container_components_t[MAX_ENTITIES]; /* container component data */

/***************************************************
 * public function prototypes
 ***************************************************/
void container_init(void);
void container_add(entity_id_t entity);
void container_remove(entity_id_t entity);

#endif // CONTAINER_COMP_H