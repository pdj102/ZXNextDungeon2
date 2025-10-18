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

#include "global_state.h"

#include "entity.h"
#include "location_comp.h"
#include "item_comp.h"
#include "creature_comp.h"

#include "util.h"

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
    entity_id_t id = entity_create(); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add item component */
    if (item_add(id, kind, quantity) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add sprite component - use item tile */
    if(sprite_add(id, item_get_tile(id)) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

entity_id_t entity_factory_create_monster(creature_kind_t kind)
{
    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add creature component */
    if (creature_add(id, kind) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add sprite component - use creature tile */
    if(sprite_add(id, creature_get_tile(id)) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

entity_id_t entity_factory_create_player( void )
{
    util_assert(g.player.id == ENTITY_ID_INVALID); /* check player entity does not exist */

    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add creature component */
    if (creature_add(id, CREATURE_HUMAN) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add sprite component - use creature tile */
    if(sprite_add(id, creature_get_tile(id)) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add player control component */
    if (player_ctrl_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

