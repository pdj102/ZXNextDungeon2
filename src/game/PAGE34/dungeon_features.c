/**
 * @file dungeon_gen.c
 * @author Paul Johnson
 * @brief
 *
 */

#include "dungeon_gen.h"

#include <stdlib.h>

#include "ecs/systems/systems_dispatch.h"

#include "game/world.h"
#include "game/map.h"
#include "game/map_terrain.h"

#include "game/PAGE34/dungeon_layout.h"

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

static void dungeon_reset_level(dungeon_transition_t *c);

static void place_stairs(dungeon_transition_t *c);
static void place_doors(dungeon_transition_t *c);
static void place_traps(dungeon_transition_t *c);

static void place_feature_in_room(feature_kind_t kind, const Room *r);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_spawn_features(dungeon_transition_t *c)
{
   place_stairs(c);
   place_doors(c);
   place_traps(c);   
}

/***************************************************
 * private functions
 ***************************************************/
static void place_stairs(dungeon_transition_t *c)
{
   Room *up_room = NULL;
   Room *down_room = NULL;
   uint8_t num_rooms = dungeon_room_count();

    if (num_rooms == 0)
        return;

    /* Depth > 0 gets upstairs */
    if (c->to_depth > 0)
    {
        up_room = pick_random_room();
        place_feature_in_room(FEATURE_UP_STAIRS, up_room);
    }

    /* All but final depth get downstairs */
    /* TODO check depth */
    down_room = pick_random_room();

    /* Avoid same room if possible */
    if (up_room && num_rooms > 1)
    {
        while (down_room == up_room)
            down_room = pick_random_room();
    }

    place_feature_in_room(FEATURE_DOWN_STAIRS, down_room);
}

static void place_doors(dungeon_transition_t *c)
{
   entity_id_t e11 = system_feature_create(FEATURE_CLOSED_DOOR);
   world_attach_entity(e11, 8, 8);
}

static void place_traps(dungeon_transition_t *c)
{
   
}

static void place_feature_in_room(feature_kind_t kind, const Room *r)
{
    int x, y;
    random_point_in_room(r, &x, &y);

    entity_id_t e = system_feature_create(kind);
    world_attach_entity(e, x, y);
}