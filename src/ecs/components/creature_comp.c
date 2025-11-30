/**
 * @file creature_comp.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "ecs/components/creature_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"
#include "ecs/components/creature_comp_priv.h"

#include "game/global_state.h"
#include "core/text.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/
/* Speed into turns and ticks conversion table (rounded)
| Speed (ft/turn) | Turns | Ticks (0–9) | Relative to Human (30 ft) |
| --------------- | ----- | ----------- | ------------------------- |
| 5               | 6     | 0           | ~6× slower                |
| 10              | 3     | 0           | ~3× slower                |
| 15              | 2     | 0           | ~2× slower                |
| 20              | 1     | 5           | 1.5× slower               |
| 25              | 1     | 2           | 1.2× slower               |
| 30              | 1     | 0           | baseline                  |
| 35              | 0     | 9           | 1.15× faster              |
| 40              | 0     | 8           | 1.3× faster               |
| 45              | 0     | 7           | 1.5× faster               |
| 50              | 0     | 6           | 1.6× faster               |
| 55              | 0     | 5           | 1.8× faster               |
| 60              | 0     | 5           | 2× faster                 |
*/
const turn_tick_t creature_speeds_conversion[SPEED_COUNT] = {
   [SPEED_NONE] = {0, 0},
   [SPEED_5FT]  = {6, 0},
   [SPEED_10FT] = {3, 0},
   [SPEED_15FT] = {2, 0},
   [SPEED_20FT] = {1, 5},
   [SPEED_25FT] = {1, 2},
   [SPEED_30FT] = {1, 0},
   [SPEED_35FT] = {0, 9},
   [SPEED_40FT] = {0, 8},
   [SPEED_45FT] = {0, 7},
   [SPEED_50FT] = {0, 6},
   [SPEED_55FT] = {0, 5},
   [SPEED_60FT] = {0, 5}
};

/***************************************************
 * public functions
 ***************************************************/
void creature_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        // g.creature_components[i].kind = CREATURE_NONE; /* mark all creatures as none */
    }
}

uint8_t creature_add(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    entity_set_component(entity, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
}

/* TODO do not do this in component */
void creature_speed_to_turns_ticks(entity_id_t id, turn_tick_t *turns_ticks)
{
    creature_speed_t speed; 

    speed = g.creature_components[id].speed;

    turns_ticks->turns = creature_speeds_conversion[speed].turns;
    turns_ticks->ticks = creature_speeds_conversion[speed].ticks;
}



void creature_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_CREATURE))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_CREATURE); /* clear entity creature component mask */
}