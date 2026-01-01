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

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/
#define MAP_WIDTH 80
#define MAP_HEIGHT 24


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
bool map_can_enter(uint8_t x, uint8_t y);
// bool map_has_line_of_sight(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
bool map_has_line_of_sight(entity_id_t e1, entity_id_t e2);

void map_gen(void);

bool in_bounds(uint8_t x, uint8_t y);
bool is_opaque(uint8_t x, uint8_t y);

#endif // MAP_H
