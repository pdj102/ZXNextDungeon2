/**
 * @file entity_factory.c
 * @author Paul Johnson
 * @brief Entity factory for ECS
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "entity_factory.h"

#include <stddef.h> /* NULL */
#include <stdint.h> /* uint8_t, uint16_t etc */
#include <sys/types.h> /* bool_t */

#include "entity.h"
#include "components/timer_comp.h"
#include "components/location_comp.h"
#include "components/item_comp.h"
#include "components/creature_comp.h"


#include "../game/global_state.h"
#include "../core/util.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * functions
 ***************************************************/

 entity_id_t entity_factory_create_item(item_kind_t kind, uint8_t quantity)
{
    zxnext_tile_t tile; 

    entity_id_t id = entity_create(); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add item component */
    if (item_add(id, kind, quantity) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add renderable component - use item tile */
    item_get_tile(id, &tile);
    if(renderable_add(id, &tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

entity_id_t entity_factory_create_monster(creature_kind_t kind)
{
    zxnext_tile_t tile; 

    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
        return id;

    entity_set_flag(id, FLAG_BLOCKING);

    /* Add creature component */
    if (creature_add(id, kind) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add renderable component - use creature tile */
    creature_get_tile(id, &tile);
    if(renderable_add(id, &tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add container component */
    if (container_add(id) == 0)
    {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

entity_id_t entity_factory_create_player( void )
{
    zxnext_tile_t tile; 
    turn_tick_t tt;

    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
        return id;

    entity_set_flag(id, FLAG_BLOCKING);

    /* Add creature component */
    if (creature_add(id, CREATURE_PLAYER) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add renderable component - use creature tile */
    creature_get_tile(id, &tile);
    if(renderable_add(id, &tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add container component */
    if (container_add(id) == 0)
    {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add player control component */
    if (player_ctrl_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add timer component*/
    if (timer_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }
    creature_speed_to_turns_ticks(id, &tt);
    text_printf(&g.msg_win, "turns:%u ticks:%u\n", tt.turns, tt.ticks);
    timer_set(id, tt.turns, tt.ticks);

    return id;
}

