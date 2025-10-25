/**
 * @file movement_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "movement_system.h"

#include <sys\types.h>

#include "entity.h"
#include "location_comp.h"

#include "../game/global_state.h"
#include "../game/map.h"
#include "../core/util.h"


/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void movement_system_init(void)
{
}

 void movement_system_try_move(entity_id_t entity, int8_t dx, int8_t dy)
 {
    uint8_t tx;
    uint8_t ty;

    tx = g.location_components[entity].x + dx;
    ty = g.location_components[entity].y + dy;

    if (map_can_enter(entity, tx, ty))
    {
        location_move(entity, tx, ty);
    }
 }
