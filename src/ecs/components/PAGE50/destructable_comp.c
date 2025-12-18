/**
 * @file destructable_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/destructable_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void destructable_init(void)
{

}

void destructable_add(entity_id_t entity, destructable_comp_t destructable_p)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_DESTRUCTABLE)); 

    g.destructable_components[entity].ac = destructable_p.ac;
    g.destructable_components[entity].cur_hp = destructable_p.cur_hp;
    g.destructable_components[entity].max_hp = destructable_p.max_hp;

    entity_set_component(entity, COMPONENT_DESTRUCTABLE); 
}

void destructable_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    entity_clear_component(entity, COMPONENT_DESTRUCTABLE); 
}