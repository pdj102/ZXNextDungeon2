/**
 * @file player_factory.c
 * @author Paul Johnson
 * @brief Player character creation and initialisation
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "player_factory.h"

#include <stdint.h>
#include <stdbool.h>      /* bool */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE46/player_progression.h"
#include "game/global_state.h"
#include "core/util.h"
#include "core/zxnext.h"

 /***************************************************
 * public functions
 ***************************************************/
entity_id_t player_factory_create(void)
{
    entity_id_t e;

    /* Create player entity */
    g.player.id = ENTITY_ID_INVALID;
    e = system_monster_create_player();
    util_assert(e != ENTITY_ID_INVALID);
    g.player.id = e;

    /* ==== initialise a default player ===*/
    g.player.xp    = 0;
    g.player.level = 1;
    g.player.class = PLAYER_CLASS_FIGHTER;

    return e;
}

