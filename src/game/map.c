/**
 * @file map.c
 * @author Paul Johnson
 * @brief Game map 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game/map.h"

#include <sys\types.h>      /* bool_t */
#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */

#include "ecs/entity.h"
#include "ecs/components/location_comp.h"

#include "game/map_terrain.h"
#include "game/PAGE34/dungeon_gen.h"
#include "game/global_state.h"

#include "core/util.h"

/***************************************************
 * private types
 * ***************************************************/


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
void map_init_cell_heads(void);

/***************************************************
 * public functions
 ***************************************************/

void map_init(void)
{
    map_terrain_init();
    map_init_cell_heads();
    g.map.camera.x = 0;
    g.map.camera.y = 0;

}

bool_t map_can_enter(entity_id_t entity, uint8_t x, uint8_t y)
{
    util_assert( entity < MAX_ENTITIES );
    util_assert( x < MAP_WIDTH);
    util_assert( y < MAP_HEIGHT);

    entity = g.map.cell_head[x][y];

    /* Check for any blocking entities*/
    while (entity != ENTITY_ID_INVALID)
    {
        if (entity_has_flag(entity, FLAG_BLOCKING))
        {
            return 0;
        }
        entity = g.location_components[entity].next_in_location;
    }

    /* Check if terrain is blocking */
    if (g.map.terrain[x][y] == TERRAIN_FLOOR)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void map_gen(void)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_DUNGEON_GEN);   /* Map dungeon generation code into ZX Spectrum 8k MMU slot 6 */    

    dungeon_gen();

    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);         
}

/***************************************************
 * private functions
 ***************************************************/
void map_init_cell_heads(void)
{
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
        for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
            g.map.cell_head[x][y] = ENTITY_ID_INVALID; /* mark all map cells as empty */
        }
    }
}