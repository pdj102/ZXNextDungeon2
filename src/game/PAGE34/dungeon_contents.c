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

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/
#define MAX_ROOMS 20

/***************************************************
 * private types
 ***************************************************/
typedef struct
{
   int x, y, w, h;
} Room;

/***************************************************
 * private variables
 * ***************************************************/
static Room rooms[MAX_ROOMS];
static int num_rooms = 0;

/***************************************************
 * private function prototypes
 ***************************************************/
static void dungeon_place_player(dungeon_transition_t *c);
static void dungeon_restore_peristent_entities(dungeon_transition_t *c);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_spawn_contents(dungeon_transition_t *c)
{
    entity_id_t e1 = system_item_create(ITEM_SHORT_SWORD, 1);
    world_attach_entity(e1, 10, 10);

    entity_id_t e2 = system_item_create(ITEM_POTION_OF_HEALING, 1);
    world_attach_entity(e2, 12, 10);

    entity_id_t e3 = system_item_create(ITEM_KEY, 1);

    entity_id_t e4 = system_monster_create(CREATURE_RAT);
    system_container_add(e4, e3);
    world_attach_entity(e4, 25, 12);

    // entity_id_t e5 = system_monster_create(CREATURE_WITHERWEED);
    // world_attach_entity(e5, 12, 12);

    entity_id_t e7 = system_item_create(ITEM_BREAD, 1);
    world_attach_entity(e7, 6, 15);

    entity_id_t e8 = system_item_create(ITEM_RING_OF_STRENGTH, 1);
    world_attach_entity(e8, 7, 15);

    entity_id_t e9 = system_item_create(ITEM_SHORT_BOW, 1);
    world_attach_entity(e9, 5, 14);

    entity_id_t e10 = system_item_create(ITEM_ARROW, 5);
    world_attach_entity(e10, 4, 14);  
}

void dungeon_place_persistents(dungeon_transition_t *c)
{
   dungeon_place_player(c);
   dungeon_restore_peristent_entities(c);
}

/***************************************************
 * private functions
 ***************************************************/

static void dungeon_place_player(dungeon_transition_t *c)
{
   world_attach_entity(g.player.id, 10, 15);
}

static void dungeon_restore_peristent_entities(dungeon_transition_t *c)
{
   
}