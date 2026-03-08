/**
 * @file player_comp.h
 * @author Paul Johnson
 * @brief 
 */

#ifndef player_comp_H
#define player_comp_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/
#define HUNGER_MAX        200u
#define HUNGER_SATIATED   150u
#define HUNGER_SATISFIED  100u
#define HUNGER_HUNGRY      50u
#define HUNGER_VERY_HUNGRY 15u
/* 0 = STARVING */

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    PLAYER_CLASS_FIGHTER = 0,
    PLAYER_CLASS_COUNT
} player_class_t;

typedef enum {
    HUNGER_STATE_SATIATED = 0,
    HUNGER_STATE_SATISFIED,
    HUNGER_STATE_HUNGRY,
    HUNGER_STATE_VERY_HUNGRY,
    HUNGER_STATE_STARVING,
} hunger_state_t;

typedef struct {
    entity_id_t    id;
    uint8_t        level;
    player_class_t class;
    uint8_t        hunger;            /* 0=STARVING, HUNGER_MAX=satiated */
    uint8_t        cur_mp;
    uint8_t        max_mp;
    uint8_t        proficiency_bonus; /* cached — recalculated on level-up only */
    uint16_t       xp;
    uint16_t       gold;
} player_comp_t;

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // player_comp_H
