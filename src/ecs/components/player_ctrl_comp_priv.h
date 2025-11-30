/**
 * @file player_ctrl_comp_priv.h
 * @brief Private/internal declarations for player_ctrl_comp.c
 *
 * This header exposes internal player_ctrl definitions only to files that need them
 * (primarily `player_ctrl_comp.c` and systems that operate on player_ctrls). It should NOT be included by general modules.
 */

#ifndef PLAYER_CTRL_COMP_PRIV_H
#define PLAYER_CTRL_COMP_PRIV_H

#include <stdint.h>

#include "player_ctrl_comp.h" /* pull in public player_ctrl_comp_type_t and PLAYER_CTRL_KIND_COUNT */

#include "ecs/entity.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Player_ctrl component data per entity */
typedef struct {
    entity_id_t id;
    entity_id_t head;
    entity_id_t neck;
    entity_id_t body;
    entity_id_t hands;
    entity_id_t left_finger;
    entity_id_t right_finger;
    entity_id_t melee_weapon;
    entity_id_t ranged_weapon;
    entity_id_t quiver;
    entity_id_t legs;
    entity_id_t feet;
} player_ctrl_comp_t;

/***************************************************
 * private function prototypes
 ***************************************************/

#endif /* PLAYER_CTRL_COMP_PRIV_H */

