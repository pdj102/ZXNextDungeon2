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
#define ENTITY_ID_INVALID 0xFF /* Invalid entity ID */

/* Component masks */
#define COMPONENT_NONE 0
#define COMPONENT_LOCATION 1 << 0
#define COMPONENT_SPRITE 1 << 1
#define COMPONENT_ITEM 1 << 2



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

typedef enum {
    ITEM_NONE = 0,
    ITEM_SWORD,
    ITEM_SHIELD,
    ITEM_POTION,
    ITEM_KEY,
    ITEM_TYPE_COUNT
} item_type_t;


/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);

entity_id_t entity_create_item(item_type_t type, uint8_t quantity);

entity_id_t entity_create(entity_type_t type);

bool_t entity_has_component(entity_id_t id, uint32_t comp_mask);
void entity_set_component(entity_id_t id, uint32_t comp_mask);
void entity_clear_component(entity_id_t id, uint32_t comp_mask);

void entity_destroy(entity_id_t id);

#endif // ENTITY_H
