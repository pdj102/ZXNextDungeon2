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
#include "game/map_access.h"

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
static void clear_terrain(void);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_reset_level(dungeon_transition_t *c)
{
   world_destroy_non_persistent_entities();
   world_detach_persistent_entities();
   clear_terrain();
}

/***************************************************
 * private functions
 ***************************************************/
static void clear_terrain(void)
{
   for (int y = 0; y < MAP_HEIGHT; ++y)
      for (int x = 0; x < MAP_WIDTH; ++x)
         map_set_terrain(x, y, TERRAIN_WALL);
}

