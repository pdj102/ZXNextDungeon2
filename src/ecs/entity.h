/**
 * @file entity.h
 * @author Paul Johnson
 * @brief Entity management for ECS
 * 
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stdbool.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAX_ENTITIES 20 /* Maximum number of entities */
#define ENTITY_ID_INVALID 0xFF /* Invalid entity ID */

/* Component masks for the various component types */
typedef enum {
    COMPONENT_MELEE_ATTACK = 0,
    COMPONENT_RANGED_ATTACK,
    COMPONENT_CONTAINED,
    COMPONENT_CONTAINER,
    COMPONENT_CREATURE,
    COMPONENT_DESTRUCTIBLE,
    COMPONENT_EQUIPPABLE,
    COMPONENT_EQUIPPED,
    COMPONENT_STACKABLE,
    COMPONENT_LOCATION,
    COMPONENT_PLAYER,
    COMPONENT_RENDERABLE,
    COMPONENT_SLOTS,
    COMPONENT_STATS,
    COMPONENT_TIMER,
    COMPONENT_EFFECT,
    COMPONENT_AI,
    COMPONENT_CONSUMABLE,
    COMPONENT_NAME,
    COMPONENT_ACTIVE_EFFECT,
    COMPONENT_AMMO,
    COMPONENT_OPENABLE,
    COMPONENT_LOCKABLE,
    COMPONENT_TRANSITION,
    COMPONENT_CONDITION,
    COMPONENT_PICKABLE,
    COMPONENT_MAX
} component_id_t;

#define FLAG_NONE               0
#define FLAG_IN_USE             1 << 0
#define FLAG_PENDING_DESTROY    1 << 1
#define FLAG_BLOCKING           1 << 2
#define FLAG_PERSISTANT         1 << 3
#define FLAG_QUEST_ITEM         1 << 4
#define FLAG_BLOCK_LOS          1 << 5

/***************************************************
 * public types
 ***************************************************/
typedef uint8_t entity_id_t; /* Type for entity IDs */



/***************************************************
 * public function prototypes
 ***************************************************/
void entity_init(void);

entity_id_t entity_create(void);

bool entity_has_component(entity_id_t id, component_id_t comp);
void entity_set_component(entity_id_t id, component_id_t comp);
void entity_clear_component(entity_id_t id, component_id_t comp);

bool entity_has_flag(entity_id_t id, uint8_t flag);
void entity_set_flag(entity_id_t id, uint8_t flag);
void entity_clear_flag(entity_id_t id, uint8_t flag);

void entity_mark_for_destruction(entity_id_t entity);
void entity_cleanup(void);


#endif // ENTITY_H
