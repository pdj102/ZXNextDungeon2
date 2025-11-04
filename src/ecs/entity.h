/**
 * @file entity.h
 * @author Paul Johnson
 * @brief Entity management for ECS
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
#define COMPONENT_RENDERABLE 1 << 1
#define COMPONENT_ITEM 1 << 2
#define COMPONENT_CREATURE 1 << 3
#define COMPONENT_CONTAINER 1 << 4
#define COMPONENT_CONTAINED 1 << 5
#define COMPONENT_PLAYER_CTRL 1 << 6
#define COMPONENT_AI_CTRL 1 << 7
#define COMPONENT_TIMER 1 << 8

#define FLAG_NONE 0
#define FLAG_IN_USE 1 << 0
#define FLAG_PENDING_DESTORY 1 << 1
#define FLAG_BLOCKING 1 << 2

/***************************************************
 * public types
 ***************************************************/
typedef uint8_t entity_id_t; /* Type for entity IDs */

typedef enum {
    DAMAGE_NONE, 
    DAMAGE_ACID,
    DAMAGE_BLUDGEONING,
    DAMAGE_COLD, 
    DAMAGE_FIRE, 
    DAMAGE_LIGHTNING, 
    DAMAGE_PIERCING, 
    DAMAGE_POISON, 
    DAMAGE_SLASHING
} damage_type_t;


/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);

entity_id_t entity_create(void);

bool_t entity_has_component(entity_id_t id, uint16_t comp_mask);
void entity_set_component(entity_id_t id, uint16_t comp_mask);
void entity_clear_component(entity_id_t id, uint16_t comp_mask);

bool_t entity_has_flag(entity_id_t id, uint8_t flag);
void entity_set_flag(entity_id_t id, uint8_t flag);
void entity_clear_flag(entity_id_t id, uint8_t flag);

void entity_clean_up(void);

void entity_destroy(entity_id_t id);

#endif // ENTITY_H
