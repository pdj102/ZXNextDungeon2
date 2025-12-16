/**
 * @file combat_system.c
 * @author Paul Johnson
 * @brief combat system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE54/combat_system.h"

#include "ecs/components/components.h"

#include "ecs/entity.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private function prototypes
 ***************************************************/
int8_t calc_melee_attack_roll(entity_id_t attacker);
bool_t attack_successful(int8_t attack_roll, entity_id_t target);
int8_t calc_melee_damage_roll(entity_id_t attacker);

/***************************************************
 * public functions
 ***************************************************/
void combat_system_init(void)
{
}

bool_t combat_system_try_melee_attack(entity_id_t attacker, entity_id_t target)
{
    int8_t attack_roll;
    int8_t damage_roll;

    /* attacker must have melee_attack and location component */
    if (!entity_has_component(attacker, COMPONENT_MELEE | COMPONENT_LOCATION ))
    {
        return 0;
    }

    /* target must have stats and location component */
    if (!entity_has_component(target, COMPONENT_STATS | COMPONENT_LOCATION))
    {
        return 0;
    }    

    /* TO DO check target within melee attack range */

    /* try attack*/

    /* attack roll */
    attack_roll = calc_melee_attack_roll(attacker);

    if (attack_successful(attack_roll, target) == 1)
    {

        system_event_emit(EVENT_ATTACKED, attacker, target, 1);

        damage_roll = calc_melee_damage_roll(attacker);

        system_damage_try_take_damage(target, damage_roll, g.melee_components[attacker].damage_type);

        return 1;
    }
    else
    {
        system_event_emit(EVENT_ATTACKED, attacker, target, 0);
        return 0;
    }
}

 
 /***************************************************
 * private functions
 ***************************************************/
/*
 * @brief Calculate melee attack roll
 *
 * attack_roll = d20 + attack modifier
 * 
 * Player melee attack 
 *      - has player, melee, stats and slots components
 *      - attack modifier = ability modifier + proficiency_bonus + weapon to hit bonus (if applicable) + other effects
 * 
 * Basic melee attack (e.g. monster)
 *      - has melee component
 *      - attack modifier = attack mod (precalculated modifier in `melee`) + other effects
 */
int8_t calc_melee_attack_roll(entity_id_t attacker)
{
    int8_t attack_mod       = 0;
    int8_t ability_mod      = 0;
    int8_t proficiency_mod  = 0;
    int8_t weapon_bonus     = 0;
    int8_t other_mod        = 0;
    int8_t d20;

    /* Step 1 - Roll 1d20 */
    d20 = game_roll_dice(DICE_1D20);

    /* Player attack */
    if (entity_has_component(attacker, COMPONENT_PLAYER | COMPONENT_MELEE | COMPONENT_STATS ))
    {
        /* Step 2 - Choose the correct ability modifier (STR or DEX) */
        ability_mod = modifiers[g.stats_components[attacker].str];

        /* Step 3 - Choose the correct proficiency modifier */
        /* TODO */

        /* Step 4 - If using a weapon determine weapon bonus*/
        if (entity_has_component(attacker, COMPONENT_SLOTS ))
        {
            if (g.slots[SLOT_HANDS] != ENTITY_ID_INVALID)
            {
                weapon_bonus = g.melee_components[g.slots[SLOT_HANDS]].hit_mod;
            }
        }

        /* Step 5 - Other to hit mods*/
        /* TODO */
        
        return d20 + ability_mod + proficiency_mod + weapon_bonus + other_mod;
    }

    /* Basic melee attack*/
    if (entity_has_component(attacker, COMPONENT_MELEE ))
    {
        /* Step 2 - Melee attack mod */
        attack_mod = g.melee_components[attacker].hit_mod;
        
        /* Step 3 - Other to hit mods*/

        return d20 + attack_mod + other_mod;
    }

    util_abort("Unknown attack type");

    return 0;
}

/* 
 * @brief returns true if the attack roll is successful 
 */
bool_t attack_successful(int8_t attack_roll, entity_id_t target)
{
    return (attack_roll >= g.stats_components[target].ac);
}
/*
 * Player melee attack 
 *      - has player, melee, stats and slots components
 *      - melee weapon 
 *              - damage roll = weapon damage roll + ability modifier + weapon to damage bonus + other effects
 *      - no melee weapon 
 *              - damage roll = melee damage roll + ability modifier + other effects
 * 
 * Basic melee attack (e.g. monster)
 *      - has melee component
 *      - damage roll = melee damage roll + other effects
 */
int8_t calc_melee_damage_roll(entity_id_t attacker)
{
    int8_t damage_roll      = 0;
    int8_t damage_bonus     = 0;
    int8_t ability_mod      = 0;
    int8_t other_mod        = 0;

    /* Player attack */
    if (entity_has_component(attacker, COMPONENT_PLAYER | COMPONENT_MELEE | COMPONENT_STATS | COMPONENT_SLOTS))
    {
        /* TODO set the entity which is the weapon to use and check has melee */
        
        if (g.slots[SLOT_HANDS] != ENTITY_ID_INVALID)
        {
            damage_roll = game_roll_dice(g.melee_components[g.slots[SLOT_HANDS]].damage_roll);
            damage_bonus = g.melee_components[g.slots[SLOT_HANDS]].damage_mod;
        }
        else
        {
            damage_roll = game_roll_dice(g.melee_components[attacker].damage_roll);
            damage_bonus = g.melee_components[attacker].damage_mod;
        }
        ability_mod = modifiers[g.stats_components[attacker].str];

        /* TODO other damage mod */

        return damage_roll + damage_bonus + ability_mod + other_mod;
    }
    /* Basic melee attack */
    if (entity_has_component(attacker, COMPONENT_MELEE))
    {
        damage_roll = game_roll_dice(g.melee_components[attacker].damage_roll);
        damage_bonus = g.melee_components[attacker].damage_mod;

        /* TODO other damage mod */

        return damage_roll +damage_bonus + other_mod;
    }

    util_abort("Unknown attack type");

    return 0;
}
