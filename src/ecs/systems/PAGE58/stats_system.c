/**
 * @file stats_system.c
 * @author Paul Johnson
 * @brief stats system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE58/stats_system.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "ecs/entity.h"

#include "game/game.h"
#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/
#define STAT_MIN 1
#define STAT_MAX 20   /* or 30 if you want giant strength */

/***************************************************
 * private function prototypes
 ***************************************************/
static inline uint8_t clamp_stat(int8_t value);

/***************************************************
 * public functions
 ***************************************************/
uint8_t stats_system_get_stat(entity_id_t actor, stat_type_t stat)
{
    int8_t value = 0;

    util_assert(entity_has_components(actor, COMPONENT_STATS));

    /* TODO Calculate the sum of active effects */
    /* val = sum */

    value += g.stats_components[actor].stats[stat];

    /* Clamp stat to between 1 and */
    return clamp_stat(value);
}

int8_t stats_system_get_stat_mod(entity_id_t actor, stat_type_t stat)
{
    return modifiers[stats_system_get_stat(actor, stat)];
}


 /***************************************************
 * private functions
 ***************************************************/

static inline uint8_t clamp_stat(int8_t value)
{
    if (value < STAT_MIN) return STAT_MIN;
    if (value > STAT_MAX) return STAT_MAX;
    return (uint8_t)value;
}
