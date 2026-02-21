/**
 * @file dungeon_layout.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef DUNGEON_LAYOUT_H
#define DUNGEON_LAYOUT_H

#include "game/PAGE34/dungeon_gen.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef struct
{
   int x, y, w, h;
} Room;

/***************************************************
 * public function prototypes
 ***************************************************/
void dungeon_build_layout(dungeon_transition_t *c);
Room *pick_random_room(void);
uint8_t dungeon_room_count(void);
const Room *dungeon_get_room(uint8_t idx);
void random_point_in_room(const Room *r, int *x, int *y);
void pick_two_distinct_rooms(Room **a, Room **b);

#endif // DUNGEON_LAYOUT_H