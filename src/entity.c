/**
 * @file entity.c
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "entity.h"

/***************************************************
 * private defines
 ***************************************************/
#define MAX_ENTITIES 10 /* Maximum number of entities */
#define ENTITY_ID_INVALID 0xFF /* Invalid entity ID */

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

static uint16_t entity_mask[MAX_ENTITIES]; /* component mask per entity */
static uint8_t entity_alive[MAX_ENTITIES]; /* 0 = free, 1 = alive */
static entity_id_t free_list[MAX_ENTITIES];
static uint8_t free_head; /* index into free_list */

/***************************************************
 * functions
 ***************************************************/

 void entity_init(void)
 {
     for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
         entity_alive[i] = 0; /* mark all entities as free */
         entity_mask[i] = 0;  /* clear all component masks */
         free_list[i] = i;    /* initialize free list */
     }
     free_head = 0; /* point to the first free entity */
 }

 entity_id_t entity_create(void)
 {
     if (free_head >= MAX_ENTITIES) {
         return ENTITY_ID_INVALID; /* no free entities */
     }
     entity_id_t id = free_list[free_head++];
     entity_alive[id] = 1; /* mark entity as alive */
     entity_mask[id] = 0;  /* clear component mask */
     return id;
 }

void entity_destroy(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !entity_alive[id]) {
        return; /* invalid ID or entity not alive */
    }
    entity_alive[id] = 0; /* mark entity as free */
    entity_mask[id] = 0;  /* clear component mask */
    free_list[--free_head] = id; /* add back to free list */
}