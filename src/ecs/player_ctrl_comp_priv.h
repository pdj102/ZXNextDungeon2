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

#include "entity.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Player_ctrl component data per entity */
typedef struct {
    entity_id_t id;
} player_ctrl_comp_t;

/***************************************************
 * private function prototypes
 ***************************************************/

#endif /* PLAYER_CTRL_COMP_PRIV_H */

