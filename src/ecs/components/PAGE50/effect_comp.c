/**
 * @file effect_comp.c
 * @author Paul Johnson
 * @brief Describes an effect that could happen 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/effect_comp.h"

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void effect_add(entity_id_t entity, const effect_comp_t effect)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EFFECT)); 

    g.effect_components[entity].kind = effect.kind;
    g.effect_components[entity].value = effect.value;
    g.effect_components[entity].duration = effect.duration;
    g.effect_components[entity].target = effect.target;
    g.effect_components[entity].triggers = effect.triggers;

    entity_set_component(entity, COMPONENT_EFFECT); /* set entity effect component mask */
}

void effect_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_EFFECT); /* clear entity effect component mask */
}

 /***************************************************
 * private functions
 ***************************************************/