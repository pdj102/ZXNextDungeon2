/**
 * @file dungeon_gen.c
 * @author Paul Johnson
 * @brief
 *
 */

#include "dungeon_layout.h"

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


/***************************************************
 * private variables
 * ***************************************************/
static Room rooms[MAX_ROOMS];
static int num_rooms = 0;

/***************************************************
 * private function prototypes
 ***************************************************/

static bool overlap(Room a, Room b);
static void make_rooms(void);
static void connect_rooms(void);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_build_layout(dungeon_transition_t *c)
{
   srand_fastcall(c->to_depth);

   num_rooms = 0;
   make_rooms();
   connect_rooms();  
}

uint8_t dungeon_room_count(void)
{
   return num_rooms;
}

Room *pick_random_room(void)
{
    if (num_rooms == 0) return NULL;
    return &rooms[rand() % num_rooms];
}

void random_point_in_room(const Room *r, int *x, int *y)
{
    *x = r->x + 1 + rand() % (r->w - 2);
    *y = r->y + 1 + rand() % (r->h - 2);
}

void pick_two_distinct_rooms(Room **a, Room **b)
{
    *a = pick_random_room();
    do {
        *b = pick_random_room();
    } while (*b == *a && num_rooms > 1);
}

/***************************************************
 * private functions
 ***************************************************/
static void make_rooms(void)
{
   for (int i = 0; i < MAX_ROOMS; i++)
   {
      Room r;
      r.w = 4 + rand() % 7;
      r.h = 4 + rand() % 5;
      r.x = 1 + rand() % (MAP_WIDTH - r.w - 2);
      r.y = 1 + rand() % (MAP_HEIGHT - r.h - 2);

      bool valid = 1;
      for (int j = 0; j < num_rooms; j++)
         if (overlap(r, rooms[j]))
         {
            valid = 0;
            break;
         }

      if (valid)
      {
         rooms[num_rooms++] = r;
         for (int y = r.y; y < r.y + r.h; ++y)
            for (int x = r.x; x < r.x + r.w; ++x)
               g.map.terrain[x][y] = TERRAIN_FLOOR;
      }
   }
}

static void connect_rooms(void)
{
   for (int i = 1; i < num_rooms; ++i)
   {
      int x1 = rooms[i - 1].x + rooms[i - 1].w / 2;
      int y1 = rooms[i - 1].y + rooms[i - 1].h / 2;
      int x2 = rooms[i].x + rooms[i].w / 2;
      int y2 = rooms[i].y + rooms[i].h / 2;

      if (rand() % 2)
      {
         // horizontal then vertical
         for (int x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++)
            g.map.terrain[x][y1] = TERRAIN_FLOOR;
         for (int y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++)
            g.map.terrain[x2][y] = TERRAIN_FLOOR;
      }
      else
      {
         // vertical then horizontal
         for (int y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++)
            g.map.terrain[x1][y] = TERRAIN_FLOOR;
         for (int x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++)
            g.map.terrain[x][y2] = TERRAIN_FLOOR;
      }
   }
}

static bool overlap(Room a, Room b)
{
   return !(a.x + a.w < b.x || b.x + b.w < a.x ||
            a.y + a.h < b.y || b.y + b.h < a.y);
}