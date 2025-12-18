/**
 * @file stats_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/PAGE50/stats_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
void stats_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        // g.stats_components[i].kind = CREATURE_NONE; /* mark all creatures as none */
    }
}

void stats_add(entity_id_t entity, stats_comp_t stats)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_components(entity, COMPONENT_STATS)); /* entity must not have creature component */

    g.stats_components[entity].speed = stats.speed;
    g.stats_components[entity].str = stats.str;
    g.stats_components[entity].dex = stats.dex;
    g.stats_components[entity].con = stats.con;    
    g.stats_components[entity].inte = stats.inte;
    g.stats_components[entity].wis = stats.wis;
    g.stats_components[entity].cha = stats.cha;

    entity_set_component(entity, COMPONENT_STATS); 
}

void stats_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    entity_clear_component(entity, COMPONENT_STATS); 
}