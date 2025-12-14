/**
 * @file actions_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "actions_system.h"

#include "ecs/entity.h"

#include "ecs/components/equippable_comp.h"
#include "ecs/components/equipped_comp.h"
#include "ecs/components/slots_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/game.h"
#include "game/global_state.h"

#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/

 /***************************************************
 * private function prototypes
 ***************************************************/
 int8_t calc_attack_roll(entity_id_t attacker, attack_type_t attack_type);

/***************************************************
 * public functions
 ***************************************************/
void actions_system_init(void)
{
}

 bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature)
{
    
}

bool_t actions_system_try_die(entity_id_t creature)
{
    system_event_emit(EVENT_DIED, creature, ENTITY_ID_INVALID, 0);

    entity_mark_for_destruction(creature);

    return 1;
}

bool_t actions_system_try_eat(entity_id_t actor, entity_id_t item)
{

}



bool_t actions_system_try_melee_attack(entity_id_t attacker, entity_id_t target)
{
    int8_t attack_roll;
    int8_t damage_roll;

    /* attacker has melee_attack, stats and location component */
    /* TODO not all attackers need stats */
    if (!entity_has_component(attacker, COMPONENT_MELEE | COMPONENT_STATS | COMPONENT_LOCATION ))
    {
        return 0;
    }

    /* target has stats and location component */
    if (!entity_has_component(target, COMPONENT_STATS | COMPONENT_LOCATION))
    {
        return 0;
    }    

    /* to do check target within melee attack range */

    /* try attack*/

    /* attack roll */
    attack_roll = calc_attack_roll(attacker, ATTACK_MELEE);
    
    /* successful hit if attack roll is greater or equal to target's armour class */
    if (attack_roll >= g.stats_components[target].ac)
    {
        /* damage roll calculation = weapon dice roll +damage_mod_bonus (which is weapon mod + ability modifer + proficiency bonus )*/
        damage_roll = game_roll_dice(g.melee_components[attacker].damage_roll);
        damage_roll += g.melee_components[attacker].damage_mod;

        system_event_emit(EVENT_ATTACKED, attacker, target, 1);

        actions_system_try_take_damage(target, damage_roll, g.melee_components[attacker].damage_type);
        return 1;
    }
    else
    {
        system_event_emit(EVENT_ATTACKED, attacker, target, 0);
        return 0;
    }
}

int8_t actions_system_try_take_damage(entity_id_t actor, int8_t damage, damage_type_t type)
{
    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.stats_components[actor].cur_hp <= damage)
    {
        g.stats_components[actor].cur_hp = 0;
        actions_system_try_die(actor);
    }
    else
    {
        g.stats_components[actor].cur_hp -= damage;
    }
    
    return damage;
}

bool_t actions_system_try_open(entity_id_t actor, entity_id_t feature)
{

}

bool_t actions_system_try_quaff(entity_id_t actor, entity_id_t item)
 {

 }

/*
 * @brief Calculate the attack roll for a given creature.
 *
 * attack_roll = d20 + attack modifier
 * 
 * For a monster the attack modifier is precalculated as melee.hit_mod or ranged.hit_mod
 * 
 * For the player attack modifier = ability_modifier + proficiency_bonus + weapon_bonus (if applicable)
 */
int8_t calc_attack_roll(entity_id_t attacker, attack_type_t attack_type)
{
    int8_t attack_mod       = 0;
    int8_t ability_mod      = 0;
    int8_t proficiency_mod  = 0;
    int8_t weapon_bonus     = 0;
    int8_t situational_mod  = 0;
    int8_t d20;

    /* Step 1 - Roll 1d20 */
    d20 = game_roll_dice(DICE_1D20);

    /* Is the attacker the player?*/
    if (attacker == g.player.id)
    {
        /* Calculate player attack roll */
        /* Step 2 - Choose the correct ability modifier (STR or DEX) */
        switch (attack_type)
        {
            case ATTACK_MELEE:
            ability_mod = modifiers[g.stats_components[attacker].str];
            break;

            case ATTACK_RANGED:
            ability_mod = modifiers[g.stats_components[attacker].dex];
            break;

            default:
            ability_mod = 0;
        }

        /* Step 3 - Choose the correct proficiency modifier */
        /* TODO */

        /* Step 4 - If using a weapon determine weapon bonus*/
        if (g.slots[SLOT_HANDS] != ENTITY_ID_INVALID)
        {
            /* TODO implement getting the weapon's attack bonus*/
        }
        
        return d20 + ability_mod + proficiency_mod + weapon_bonus + situational_mod;
    }
    else
    {
        /* Calculate monster attack roll */
        switch (attack_type)
        {
            case ATTACK_MELEE:
            attack_mod = g.melee_components[attacker].hit_mod;
            break;

            case ATTACK_RANGED:
            attack_mod = g.ranged_components[attacker].hit_mod;
            break;

            default:
            attack_mod = 0;
        }
        return d20 + attack_mod;
    }    
}