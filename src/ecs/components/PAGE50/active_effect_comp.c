/**
 * @file active_effect_comp.c
 * @author Paul Johnson
 * @brief Describes an active effect 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/active_effect_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void active_effect_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_ACTIVE_EFFECT)); 

    entity_set_component(entity, COMPONENT_ACTIVE_EFFECT); 
}

void active_effect_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_ACTIVE_EFFECT);
}

 /***************************************************
 * private functions
 ***************************************************/