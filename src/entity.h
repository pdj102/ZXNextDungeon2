/**
 * @file entity.h
 * @author Paul Johnson
 * @brief Entity management for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <sys/types.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAX_ENTITIES 10 /* Maximum number of entities */
#define ENTITY_ID_INVALID 0xFF /* Invalid entity ID */

/* Component masks for the various component types */
#define COMPONENT_NONE 0
#define COMPONENT_LOCATION 1 << 0
#define COMPONENT_SPRITE 1 << 1
#define COMPONENT_ITEM 1 << 2
#define COMPONENT_CREATURE 1 << 3
#define COMPONENT_CONTAINER 1 << 4
#define COMPONENT_PLAYER_CTRL 1 << 5
#define COMPONENT_AI_CTRL 1 << 6

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
    ENTITY_KIND_COUNT
} entity_kind_t;


/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);

entity_id_t entity_create(entity_kind_t kind);

bool_t entity_has_component(entity_id_t id, uint32_t comp_mask);
void entity_set_component(entity_id_t id, uint32_t comp_mask);
void entity_clear_component(entity_id_t id, uint32_t comp_mask);

void entity_destroy(entity_id_t id);

#endif // ENTITY_H
