/**
 * @file ai_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef AI_COMP_H
#define AI_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

#include "core/text.h"

/***************************************************
 * public defines
 ***************************************************/
typedef enum {
    AI_STATE_NONE,
    AI_STATE_IDLE,        // Not aware of player
    AI_STATE_WANDER,      // Roaming around
    AI_STATE_ALERT,       // Heard/saw something suspicious
    AI_STATE_CHASE,       // Actively pursuing target
    AI_STATE_ATTACK,      // In melee / ready to attack
    AI_STATE_FLEE,        // Low HP or afraid
    AI_STATE_SLEEP,      // Asleep until disturbed
    AI_STATE_DEAD
} ai_state_t;

typedef struct {
    ai_state_t state;
    entity_id_t target;      // usually the player
    uint8_t alert_timer;     // how many turns the monster stays alert
    uint8_t last_seen_x;
    uint8_t last_seen_y;
} ai_comp_t;


/***************************************************
 * public types
 ***************************************************/
typedef ai_comp_t ai_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/


#endif // AI_COMP_H
