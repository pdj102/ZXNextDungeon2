/**
 * @file entity.h
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAX_ENTITIES 10 /* Maximum number of entities */
#define ENTITY_ID_INVALID 0xFF /* Invalid entity ID */

#define COMPONENT_ITEM 1 << 0

/* all entities have a location component */

/***************************************************
 * public types
 ***************************************************/
typedef uint8_t entity_id_t; /* Type for entity IDs */

typedef enum {
    ENTITY_NONE = 0,
    ENTITY_PLAYER,
    ENTITY_MONSTER,
    ENTITY_ITEM,
    ENTITY_CHEST,
    ENTITY_DOOR,
    ENTITY_EFFECT,
    ENTITY_TYPE_COUNT
} entity_type_t;

typedef struct { 
    uint16_t mask; /* component mask */
    uint8_t alive; /* 0 = free, 1 = alive */
    entity_type_t type; /* type of entity */
} entity_t;

typedef struct {
    entity_t entities[MAX_ENTITIES]; /* array of entities */
    entity_id_t free_ids[MAX_ENTITIES]; /* stack of free entity IDs */
    uint8_t free_head; /* index of the top of the free stack */
} entity_arena_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);
entity_id_t entity_create(void);
entity_id_t *entity_get(entity_id_t id);
void entity_destroy(entity_id_t id);

#endif // ENTITY_H
