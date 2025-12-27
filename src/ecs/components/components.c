/**
 * @file components.c
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/entity.h"

#include "core/util.h"

/***************************************************
 * private variables
 ****************************************************/


/***************************************************
 * public functions
 ***************************************************/
void component_init(void)
{
    
}

 void component_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_ACTIVE_EFFECT)); 

    entity_set_component(entity, COMPONENT_ACTIVE_EFFECT); 
}

void component_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_ACTIVE_EFFECT);
}

 /***************************************************
 * private functions
 ***************************************************/