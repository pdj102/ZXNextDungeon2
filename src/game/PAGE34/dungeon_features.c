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
#include "game/map_access.h"

#include "game/PAGE34/dungeon_layout.h"

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/
#define MAX_DOORS           5
#define MAX_DOOR_CANDIDATES 80

/***************************************************
 * private types
 ***************************************************/
typedef struct {
    uint8_t x;
    uint8_t y;
} door_candidate_t;

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

static bool    is_valid_doorway(uint8_t px, uint8_t ox, uint8_t oy);
static uint8_t collect_door_candidates(door_candidate_t *candidates, uint8_t max);
static void    select_doors(door_candidate_t *candidates, uint8_t count);

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

    /* Place upstairs in a random room */
    up_room = pick_random_room();
    place_feature_in_room(FEATURE_UP_STAIRS, up_room);

    /* All but final depth get downstairs */
    /* TODO check depth and do not place on lowest level */
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
    door_candidate_t candidates[MAX_DOOR_CANDIDATES];
    uint8_t count;
    uint8_t num_doors;
    uint8_t i;
    entity_id_t door;

    (void)c; /* reserved: future depth-scaled door density */

    if (dungeon_room_count() == 0)
        return;

    count = collect_door_candidates(candidates, MAX_DOOR_CANDIDATES);
    if (count == 0)
        return;

    select_doors(candidates, count);
    num_doors = count < MAX_DOORS ? count : MAX_DOORS;

    for (i = 0; i < num_doors; ++i)
    {
        door = system_feature_create(FEATURE_CLOSED_DOOR);
        if (door == ENTITY_ID_INVALID)
            return;
        world_attach_entity(door, candidates[i].x, candidates[i].y);
    }
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

/*
 * @brief Check whether a room-perimeter cell has a corridor entrance that
 *        forms a genuine choke point (corridor is exactly 1 tile wide).
 *
 * @param px  Perimeter cell x (on the room edge)
 * @param py  Perimeter cell y (on the room edge)
 * @param ox  Outer cell x (just outside the room, candidate door position)
 * @param oy  Outer cell y (just outside the room, candidate door position)
 * @return true if (ox, oy) is a valid choke-point doorway
 */
static bool is_valid_doorway(uint8_t px, uint8_t ox, uint8_t oy)
{
    /* Outer cell must be floor (corridor present) */
    if (map_get_terrain(ox, oy) != TERRAIN_FLOOR)
        return false;

    if (px == ox)
    {
        /* Top or bottom wall: corridor approaches vertically.
         * Flanking cells are left and right of the outer cell. */
        if (ox == 0 || ox >= MAP_WIDTH - 1)
            return false;
        return map_get_terrain(ox - 1, oy) == TERRAIN_WALL &&
               map_get_terrain(ox + 1, oy) == TERRAIN_WALL;
    }
    else
    {
        /* Left or right wall: corridor approaches horizontally.
         * Flanking cells are above and below the outer cell. */
        if (oy == 0 || oy >= MAP_HEIGHT - 1)
            return false;
        return map_get_terrain(ox, oy - 1) == TERRAIN_WALL &&
               map_get_terrain(ox, oy + 1) == TERRAIN_WALL;
    }
}

/*
 * @brief Scan all room perimeters for corridor entrances and collect
 *        valid choke-point doorway positions.
 *
 * Corner cells are excluded: corridors enter via L-shaped paths and
 * cannot enter diagonally through corners.
 *
 * The door is placed at the outer cell (ox, oy) — the last corridor
 * tile before the room boundary — not inside the room itself.
 *
 * @param candidates  Output array of doorway positions
 * @param max         Capacity of candidates array
 * @return            Number of candidates found
 */
static uint8_t collect_door_candidates(door_candidate_t *candidates, uint8_t max)
{
    uint8_t n = 0;
    uint8_t num_rooms = dungeon_room_count();
    uint8_t i;

    for (i = 0; i < num_rooms; ++i)
    {
        const Room *r = dungeon_get_room(i);
        int px, py, ox, oy;

        /* Top wall: perimeter y = r->y, outer y = r->y-1
         * Scan x excluding corners: [r->x+1 .. r->x+r->w-2] */
        py = r->y;
        oy = r->y - 1;
        for (px = r->x + 1; px <= r->x + r->w - 2; ++px)
        {
            if (n >= max) return n;
            if (is_valid_doorway((uint8_t)px, (uint8_t)px, (uint8_t)oy))
            {
                candidates[n].x = (uint8_t)px;
                candidates[n].y = (uint8_t)oy;
                ++n;
            }
        }

        /* Bottom wall: perimeter y = r->y+r->h-1, outer y = r->y+r->h */
        py = r->y + r->h - 1;
        oy = r->y + r->h;
        for (px = r->x + 1; px <= r->x + r->w - 2; ++px)
        {
            if (n >= max) return n;
            if (is_valid_doorway((uint8_t)px, (uint8_t)px, (uint8_t)oy))
            {
                candidates[n].x = (uint8_t)px;
                candidates[n].y = (uint8_t)oy;
                ++n;
            }
        }

        /* Left wall: perimeter x = r->x, outer x = r->x-1
         * Scan y excluding corners: [r->y+1 .. r->y+r->h-2] */
        px = r->x;
        ox = r->x - 1;
        for (py = r->y + 1; py <= r->y + r->h - 2; ++py)
        {
            if (n >= max) return n;
            if (is_valid_doorway((uint8_t)px, (uint8_t)ox, (uint8_t)py))
            {
                candidates[n].x = (uint8_t)ox;
                candidates[n].y = (uint8_t)py;
                ++n;
            }
        }

        /* Right wall: perimeter x = r->x+r->w-1, outer x = r->x+r->w */
        px = r->x + r->w - 1;
        ox = r->x + r->w;
        for (py = r->y + 1; py <= r->y + r->h - 2; ++py)
        {
            if (n >= max) return n;
            if (is_valid_doorway((uint8_t)px, (uint8_t)ox, (uint8_t)py))
            {
                candidates[n].x = (uint8_t)ox;
                candidates[n].y = (uint8_t)py;
                ++n;
            }
        }
    }

    return n;
}

/*
 * @brief Randomly select up to MAX_DOORS candidates using a partial
 *        Fisher-Yates shuffle. After this call, candidates[0..limit-1]
 *        hold the selected door positions.
 *
 * @param candidates  Array of doorway candidates (modified in place)
 * @param count       Total number of candidates
 */
static void select_doors(door_candidate_t *candidates, uint8_t count)
{
    uint8_t limit = count < MAX_DOORS ? count : MAX_DOORS;
    uint8_t i;

    for (i = 0; i < limit; ++i)
    {
        uint8_t j = i + (uint8_t)(rand() % (count - i));
        door_candidate_t tmp = candidates[i];
        candidates[i] = candidates[j];
        candidates[j] = tmp;
    }
}
