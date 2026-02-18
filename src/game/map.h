/**
 * @file map.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_H
#define MAP_H

#include "ecs/entity.h"

#include "game/spatial.h"
#include "game/PAGE34/dungeon_gen.h"
#include "game/map_terrain.h"

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAP_WIDTH 80
#define MAP_HEIGHT 48

/***************************************************
 * public types
 ***************************************************/


/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * public function prototypes
 ***************************************************/
void map_init(void);

entity_id_t map_get_first(uint8_t x, uint8_t y);
entity_id_t map_get_next(entity_id_t id);

bool map_can_enter(uint8_t x, uint8_t y);
bool map_has_line_of_sight(coord_t *a, coord_t *b);

void map_gen(dungeon_transition_t *c);

bool map_in_bounds(uint8_t x, uint8_t y);
bool map_is_opaque(uint8_t x, uint8_t y);

/* Inline accessor functions are defined in map_access.h
 * (include map_access.h after global_state.h to use them) */

#endif // MAP_H
