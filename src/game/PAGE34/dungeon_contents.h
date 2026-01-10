/**
 * @file dungeon_contents.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef DUNGEON_CONTENTS_H
#define DUNGEON_CONTENTS_H

#include "game/PAGE34/dungeon_gen.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/
void dungeon_spawn_contents(dungeon_transition_t *c);
void dungeon_place_persistents(dungeon_transition_t *c);

#endif // DUNGEON_CONTENTS_H
