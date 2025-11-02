/**
 * @file dungeon_gen.c
 * @author Paul Johnson
 * @brief
 *
 */

#include "dungeon_gen.h"

#include <stdlib.h>

#include "../map.h"
#include "../map_terrain.h"

#include "../global_state.h"

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
Room rooms[MAX_ROOMS];
int num_rooms = 0;

/***************************************************
 * private function prototypes
 ***************************************************/

void clear_map(void);
bool_t overlap(Room a, Room b);
void make_rooms(void);
void connect_rooms(void);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_gen(void)
{
   clear_map();
   make_rooms();
   connect_rooms();
}

/***************************************************
 * private functions
 ***************************************************/
void clear_map(void)
{
   for (int y = 0; y < MAP_HEIGHT; ++y)
      for (int x = 0; x < MAP_WIDTH; ++x)
         g.map.terrain[x][y] = TERRAIN_WALL;
}

bool_t overlap(Room a, Room b)
{
   return !(a.x + a.w < b.x || b.x + b.w < a.x ||
            a.y + a.h < b.y || b.y + b.h < a.y);
}

void make_rooms(void)
{
   for (int i = 0; i < MAX_ROOMS; i++)
   {
      Room r;
      r.w = 4 + rand() % 7;
      r.h = 4 + rand() % 5;
      r.x = 1 + rand() % (MAP_WIDTH - r.w - 2);
      r.y = 1 + rand() % (MAP_HEIGHT - r.h - 2);

      bool_t valid = 1;
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

void connect_rooms(void)
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