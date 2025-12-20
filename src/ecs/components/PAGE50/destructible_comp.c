/**
 * @file destructible_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/destructible_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void destructible_add(entity_id_t entity, const destructible_comp_t destructible)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_DESTRUCTIBLE)); 

    g.destructible_components[entity].ac = destructible.ac;
    g.destructible_components[entity].cur_hp = destructible.cur_hp;
    g.destructible_components[entity].max_hp = destructible.max_hp;
    g.destructible_components[entity].immune = destructible.immune;
    g.destructible_components[entity].resist = destructible.resist;
    g.destructible_components[entity].vulnerable = destructible.vulnerable;


    entity_set_component(entity, COMPONENT_DESTRUCTIBLE); 
}

void destructible_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    entity_clear_component(entity, COMPONENT_DESTRUCTIBLE); 
}