/**
 * @file consumable_comp.c
 * @author Paul Johnson
 * @brief ECS consumable component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/consumable_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void consumable_init(void)
{

}

void consumable_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CONSUMABLE)); 

    entity_set_component(entity, COMPONENT_CONSUMABLE); 
}

void consumable_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_CONSUMABLE); 
}

 /***************************************************
 * private functions
 ***************************************************/