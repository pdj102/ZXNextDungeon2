/**
 * @file map.c
 * @author Paul Johnson
 * @brief Game map 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/map.h"

#include <stdbool.h>      /* bool */
#include <stdlib.h>         /* abs() */
#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */

#include "ecs/entity.h"

#include "game/map_terrain.h"
#include "game/PAGE34/dungeon_gen.h"
#include "game/global_state.h"
#include "game/memory_map.h"

#include "core/util.h"

#define MAX_VIEW_DISTANCE 10

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void map_init_cell_heads(void);
static bool can_enter(uint8_t x, uint8_t y);

/***************************************************
 * public functions
 ***************************************************/

void map_init(void)
{
    map_terrain_init();
    map_init_cell_heads();
}

bool map_can_enter(uint8_t x, uint8_t y)
{
    util_assert( x < MAP_WIDTH);
    util_assert( y < MAP_HEIGHT);

    return can_enter(x, y);
}

entity_id_t map_get_first(uint8_t x, uint8_t y)
{
    return g.map.cell_head[x][y];
}

bool map_has_line_of_sight(coord_t *a, coord_t *b)
{
    line_stepper_t ls;
    line_stepper_init(&ls, a->x, a->y, b->x, b->y);

    // Skip the starting tile
    while (line_stepper_step(&ls))
    {
        if (!in_bounds(ls.x0, ls.y0))
            return false;

        if (is_opaque(ls.x0, ls.y0))
            return false;
    }

    return true;
}

void map_gen(dungeon_transition_t *c)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_DUNGEON_GEN);   /* Map dungeon generation code into ZX Spectrum 8k MMU slot 6 */    

    dungeon_generate(c);

    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);         
}

/* 
 * @brief check if x,y is within map
 */
bool in_bounds(uint8_t x, uint8_t y)
{
    return ((x < MAP_WIDTH) && (y < MAP_HEIGHT));
}

bool is_opaque(uint8_t x, uint8_t y)
{
    if (g.map.terrain[x][y] == TERRAIN_FLOOR)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/***************************************************
 * private functions
 ***************************************************/

 /*
  * @brief mark all map cells as empty
  */
static void map_init_cell_heads(void)
{
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
            g.map.cell_head[x][y] = ENTITY_ID_INVALID; 
        }
    }
}

/*
 * @brief returns 1 if cell is not blocked by terrain or entities
 */
static bool can_enter(uint8_t x, uint8_t y)
{
    entity_id_t entity;

    /* Check if terrain is blocking */
    if (g.map.terrain[x][y] != TERRAIN_FLOOR)
    {
        return 0;
    }

    /* Check for any blocking entities*/
    entity = g.map.cell_head[x][y];

    while (entity != ENTITY_ID_INVALID)
    {
        if (entity_has_flag(entity, FLAG_BLOCKING))
        {
            return 0;
        }
        entity = g.location_components[entity].next_in_location;
    }
    return 1;
}