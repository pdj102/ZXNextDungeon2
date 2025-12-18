/**
 * @file attack_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/PAGE50/attack_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void attack_init(void)
{

}

void melee_add(entity_id_t entity, const attack_comp_t attack)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_components(entity, COMPONENT_MELEE)); 

    g.melee_components[entity].damage_type = attack.damage_type;
    g.melee_components[entity].damage_roll = attack.damage_roll;
    g.melee_components[entity].damage_mod = attack.damage_mod;
    g.melee_components[entity].hit_mod = attack.hit_mod;
    g.melee_components[entity].range = attack.range;

    entity_set_component(entity, COMPONENT_MELEE); 
}

void ranged_add(entity_id_t entity, const attack_comp_t attack)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_components(entity, COMPONENT_RANGED)); 

    g.melee_components[entity].damage_type = attack.damage_type;
    g.melee_components[entity].damage_roll = attack.damage_roll;
    g.melee_components[entity].damage_mod = attack.damage_mod;
    g.melee_components[entity].hit_mod = attack.hit_mod;
    g.melee_components[entity].range = attack.range;

    entity_set_component(entity, COMPONENT_RANGED); 
}

void melee_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_MELEE); 
}

void ranged_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_RANGED); 
}

 /***************************************************
 * private functions
 ***************************************************/