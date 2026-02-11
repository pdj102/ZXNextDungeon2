/**
 * @file ai_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef AI_COMP_H
#define AI_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/spatial.h"

#include "core/util.h"
#include "core/text.h"

/***************************************************
 * public defines
 ***************************************************/
typedef enum {
    AI_STATE_NONE,
    AI_STATE_SLEEP,             // Asleep until disturbed    
    AI_STATE_IDLE,              // Not aware of player
    AI_STATE_WANDER,            // Roaming around
    AI_STATE_ATTACK_TARGET,     // Move towards target and melee attack 
    AI_STATE_TRACK_TARGET,      // Move towards target's last known position
    AI_STATE_SEARCH_TARGET,     // Search for target
    AI_STATE_FLEE,              // Low HP or afraid
} ai_state_t;

typedef struct {
    ai_state_t state;
    entity_id_t target;      // usually the player
    uint8_t search_timer;    // how many turns the monster will search
    uint8_t stuck_counter;   // consecutive failed movement attempts
    coord_t last_seen;
} ai_comp_t;


/***************************************************
 * public types
 ***************************************************/
typedef ai_comp_t ai_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/


#endif // AI_COMP_H
