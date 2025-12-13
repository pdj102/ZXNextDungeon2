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
/* Speed into turns and ticks conversion table (rounded)
| Speed (ft/turn) | Turns | Ticks (0–9) | Total Ticks   | Relative to Human (30 ft) |
| --------------- | ----- | ----------- | -----------   | ------------------------- |
| 5               | 6     | 0           | 60            |~6× slower                 |
| 10              | 3     | 0           | 30            | ~3× slower                |
| 15              | 2     | 0           | 20            | ~2× slower                |
| 20              | 1     | 5           | 15            | 1.5× slower               |
| 25              | 1     | 2           | 12            | 1.2× slower               |
| 30              | 1     | 0           | 10            | baseline                  |
| 35              | 0     | 9           |  9            | 1.15× faster              |
| 40              | 0     | 8           |  8            | 1.3× faster               |
| 45              | 0     | 7           |  7            | 1.5× faster               |
| 50              | 0     | 6           |  6            | 1.6× faster               |
| 55              | 0     | 5           |  5            | 1.8× faster               |
| 60              | 0     | 4           |  4            | ~2× faster                |
*/
const ticks_t speed_to_ticks_table[SPEED_COUNT] = {
   [SPEED_NONE] = 0,
   [SPEED_5FT]  = 60,
   [SPEED_10FT] = 30,
   [SPEED_15FT] = 20,
   [SPEED_20FT] = 15,
   [SPEED_25FT] = 12,
   [SPEED_30FT] = 10,
   [SPEED_35FT] = 9,
   [SPEED_40FT] = 8,
   [SPEED_45FT] = 7,
   [SPEED_50FT] = 6,
   [SPEED_55FT] = 5,
   [SPEED_60FT] = 4
};


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

/* TODO do not do this in component */
ticks_t speed_to_ticks(speed_t speed)
{
    return speed_to_ticks_table[speed];
}

void stats_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);

    entity_clear_component(entity, COMPONENT_STATS); 
}