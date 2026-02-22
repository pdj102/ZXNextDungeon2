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

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/
#define STAT_MIN 1
#define STAT_MAX 20   /* or 30 if you want giant strength */

/***************************************************
 * private variables
 ***************************************************/
static const int8_t modifiers[] = { -5, -4, -4, -3, -3, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10}; 

/***************************************************
 * private function prototypes
 ***************************************************/
static inline uint8_t clamp_stat(int8_t value);


/***************************************************
 * public functions
 ***************************************************/
uint8_t stats_system_get_stat_cur(entity_id_t actor, stat_kind_t stat)
{
    int8_t value;

    util_assert(entity_has_component(actor, COMPONENT_STATS));

    value = g.stats_components[actor].stats[stat];

    switch (stat)
    {
        case STAT_STR:
            value += system_effect_mod_sum(actor, ATTRIBUTE_STR);
            break;
        case STAT_DEX:
            value += system_effect_mod_sum(actor, ATTRIBUTE_DEX);
            break;
        case STAT_CON:
            value += system_effect_mod_sum(actor, ATTRIBUTE_CON);
            break;
        case STAT_INT:
            value += system_effect_mod_sum(actor, ATTRIBUTE_INT);
            break;
        case STAT_WIS:
            value += system_effect_mod_sum(actor, ATTRIBUTE_WIS);
            break;
        case STAT_CHA:
            value += system_effect_mod_sum(actor, ATTRIBUTE_CHA);
            break;
        default:
            return 100;
    }
    return clamp_stat(value);
}

uint8_t stats_system_get_stat_base(entity_id_t actor, stat_kind_t stat)
{
     util_assert(entity_has_component(actor, COMPONENT_STATS));

    return g.stats_components[actor].stats[stat];
}

/*
 * @brief Returns abilty stat modifier e.g. 10 > 0, 12 > +1 
 */
int8_t stats_system_get_stat_modifier(entity_id_t actor, stat_kind_t stat)
{
    return modifiers[stats_system_get_stat_cur(actor, stat)];
}

uint8_t stats_system_get_speed_cur(entity_id_t actor)
{
    int8_t value;

    util_assert(entity_has_component(actor, COMPONENT_STATS));

    value = g.stats_components[actor].speed;

    value += system_effect_mod_sum(actor, ATTRIBUTE_SPEED);

    value = value < 1 ? 1 : value;

    return value;
}

uint8_t stats_system_get_speed_base(entity_id_t actor)
{
    util_assert(entity_has_component(actor, COMPONENT_STATS));

    return g.stats_components[actor].speed;
}

uint8_t stats_system_get_ac_cur(entity_id_t actor)
{
    int8_t value;

    util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    value = g.destructible_components[actor].ac;

    value += system_effect_mod_sum(actor, ATTRIBUTE_ARMOR_CLASS);

    value = value < 1 ? 1 : value;

    return value;
}

uint8_t stats_system_get_ac_base(entity_id_t actor)
{
    util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    return g.destructible_components[actor].ac;
}

uint8_t stats_system_get_hp_cur(entity_id_t actor)
{
    util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    return g.destructible_components[actor].cur_hp;
}

uint8_t stats_system_get_hp_max(entity_id_t actor)
{
    int8_t value;

    util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    value = g.destructible_components[actor].max_hp;

    value += system_effect_mod_sum(actor, ATTRIBUTE_MAX_HP);

    value = value < 1 ? 1 : value;

    return value;
}

uint8_t stats_system_get_mp_cur(entity_id_t actor)
{
    /* TODO Implement mana points e.g. magic component or as part of stats component */

    // util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    // return g.destructible_components[actor].cur_mp;

    return 0;
}

uint8_t stats_system_get_mp_max(entity_id_t actor)
{
    /* TODO Implement mana points e.g. magic component or as part of stats component */
    // int8_t value;

    // util_assert(entity_has_component(actor, COMPONENT_DESTRUCTIBLE));

    // value = g.destructible_components[actor].max_mp;

    // value += system_effect_mod_sum(actor, ATTRIBUTE_MAX_MP);

    // value = value < 1 ? 1 : value;

    // return value;

    return 0;
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

