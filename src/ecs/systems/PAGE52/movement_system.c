/**
 * @file movement_system.c
 * @author Paul Johnson
 * @brief movement system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE52/movement_system.h"

#include "ecs/components/components.h"
#include "ecs/components/PAGE50/location_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/

 bool_t movement_system_try_move(entity_id_t actor, int8_t dx, int8_t dy)
 {
    uint8_t tx;
    uint8_t ty;

    tx = g.location_components[actor].x + dx;
    ty = g.location_components[actor].y + dy;

    if (map_can_enter(actor, tx, ty))
    {
        comp_location_move(actor, tx, ty);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool_t movement_system_location_equal(entity_id_t entity1, entity_id_t entity2)
{
    util_assert(entity1 < MAX_ENTITIES);
    util_assert(entity2 < MAX_ENTITIES);
    util_assert(entity_has_component(entity1, COMPONENT_LOCATION));
    util_assert(entity_has_component(entity2, COMPONENT_LOCATION));

    if ((g.location_components[entity1].x == g.location_components[entity2].x) &&
        (g.location_components[entity1].y == g.location_components[entity2].y))
    {
        return 1;
    }
    return 0;
}

 /***************************************************
 * private functions
 ***************************************************/
