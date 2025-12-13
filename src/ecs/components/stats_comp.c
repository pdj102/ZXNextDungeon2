/**
 * @file stats_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/stats_comp.h"

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

uint8_t stats_add(entity_id_t entity, stats_comp_t *stats_p)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_STATS)); /* entity must not have creature component */

    g.stats_components[entity].ac = stats_p->ac;
    g.stats_components[entity].cur_hp = stats_p->cur_hp;
    g.stats_components[entity].max_hp = stats_p->max_hp;
    g.stats_components[entity].speed = stats_p->speed;
    g.stats_components[entity].str = stats_p->str;
    g.stats_components[entity].dex = stats_p->dex;
    g.stats_components[entity].con = stats_p->con;    
    g.stats_components[entity].inte = stats_p->inte;
    g.stats_components[entity].wis = stats_p->wis;
    g.stats_components[entity].cha = stats_p->cha;

    entity_set_component(entity, COMPONENT_STATS); 

    return 1; /* success */
}

void stats_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    entity_clear_component(entity, COMPONENT_STATS); 
}