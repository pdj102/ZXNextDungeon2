/**
 * @file combat_system.c
 * @author Paul Johnson
 * @brief combat system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE54/combat_system.h"

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/game.h"
#include "game/global_state.h"
#include "game/map_terrain.h"

/***************************************************
 * private types
 ***************************************************/
typedef struct {
    int8_t d20;      /* raw d20 roll (1–20) */
    int8_t total;    /* d20 + all modifiers */
} attack_roll_t;

/***************************************************
 * private function prototypes
 ***************************************************/
static attack_roll_t roll_melee_attack(entity_id_t attacker);
static int8_t calc_player_melee_attack_bonus(entity_id_t attacker);
static int8_t calc_basic_melee_attack_bonus(entity_id_t attacker);
static attack_result_t resolve_attack(attack_roll_t roll, entity_id_t target);

static int8_t roll_melee_damage(entity_id_t attacker, bool_t is_critical);
static int8_t calc_player_melee_damage_roll(entity_id_t attacker,bool_t is_critical);
static int8_t calc_basic_melee_damage_roll(entity_id_t attacker, bool_t is_critical);

static bool_t wielding_melee_weapon(entity_id_t actor);
static entity_id_t get_melee_source(entity_id_t attacker);
static uint8_t roll_damage_dice(dice_roll_t dice, bool_t crit);


/***************************************************
 * public functions
 ***************************************************/
void combat_system_init(void)
{
}

bool_t combat_system_try_melee_attack(entity_id_t attacker, entity_id_t target)
{
    attack_roll_t attack_roll;
    damage_type_t damage_type;
    uint8_t damage_roll;

    /* attacker must have melee_attack and location component */
    if (!entity_has_component(attacker, COMPONENT_MELEE_ATTACK))
    {
        return 0;
    }
    if (!entity_has_component(attacker, COMPONENT_LOCATION ))
    {
        return 0;
    }    

    /* target must have stats and location component */
    if (!entity_has_component(target, COMPONENT_DESTRUCTABLE))
    {
        return 0;
    }
    if (!entity_has_component(target, COMPONENT_LOCATION))
    {
        return 0;
    }        

    /* TODO: check target within melee attack range */

    /* Attack roll */
    attack_roll = roll_melee_attack(attacker);

    /* Get the damage type of the weapon or basic melee attack */
    if (wielding_melee_weapon(attacker))
    {
        damage_type = g.melee_components[g.slots[SLOT_HANDS]].damage_type;
    }
    else
    {
        damage_type = g.melee_components[attacker].damage_type;
    }

    /* Resolve attack result */
    switch (resolve_attack(attack_roll, target))
    {
        case ATTACK_CRITICAL:
            /* crit damage */
            system_event_emit(EVENT_ATTACKED, attacker, target, ATTACK_CRITICAL);
            damage_roll = roll_melee_damage(attacker, 1);
            system_damage_try_take_damage(target, damage_roll, damage_type);
            return 1;

        case ATTACK_HIT:
            /* normal damage */
            system_event_emit(EVENT_ATTACKED, attacker, target, ATTACK_HIT);
            damage_roll = roll_melee_damage(attacker, 0);
            system_damage_try_take_damage(target, damage_roll, damage_type);
            return 1;

        case ATTACK_MISS:
            /* nothing */
            system_event_emit(EVENT_ATTACKED, attacker, target, 0);
            return 0;
        default:
            util_abort("Unknown attack roll result");
            break;
    }

    return 0;
}

 
 /***************************************************
 * private functions
 ***************************************************/


static attack_roll_t roll_melee_attack(entity_id_t attacker)
{
    attack_roll_t roll;
    int8_t bonus = 0;

    /* Step 1 – Determine attack bonus source */
    if (entity_has_component(attacker, COMPONENT_PLAYER))
    {
        bonus = calc_player_melee_attack_bonus(attacker);
    }
    else if (entity_has_component(attacker, COMPONENT_MELEE_ATTACK))
    {
        bonus = calc_basic_melee_attack_bonus(attacker);
    }
    else
    {
        util_abort("Entity cannot perform melee attack");
    }

    /* Step 2 – Roll d20 (handle advantage later if needed) */
    roll.d20 = game_roll_dice(DICE_1D20);

    /* Step 3 - Calculate total attack roll */
    roll.total = roll.d20 + bonus;

    /* Clamp to 1 or higher*/
    if (roll.total < 1) 
    { 
        roll.total = 1;
    }

    return roll;
}


 /*
 * @details Calculate player melee attack bonus
 */
static int8_t calc_player_melee_attack_bonus(entity_id_t attacker)
{
    int8_t attack_bonus = 0;
    int8_t ability_mod = 0;
    int8_t proficiency_mod = 0;
    int8_t other_mods = 0;
    entity_id_t melee_source = ENTITY_ID_INVALID;

    util_assert(entity_has_component(attacker, COMPONENT_PLAYER));
    util_assert(entity_has_component(attacker, COMPONENT_MELEE_ATTACK));
    util_assert(entity_has_component(attacker, COMPONENT_STATS));

    /* Determine melee source entity, attacker if unarmed / natural attack or weapon entity if a melee weapon is being wielded */
    melee_source = get_melee_source(attacker);

    attack_bonus = g.melee_components[melee_source].hit_mod;

    // ability_mod = modifiers[g.stats_components[attacker].str];
    ability_mod = system_stats_get_stat_mod(attacker, STAT_STR);

    if (wielding_melee_weapon(attacker))
    {
        /* TODO: If finesse weapon - ability mod is DEX if DEX > STR*/
        
        /* TODO: if proficient with weapon, determine proficiency bonus */
    }

    /* TODO: Other effects (buffs, conditions)
    other_mods = effects_to_hit_bonus(attacker);
    */

    return attack_bonus + ability_mod + proficiency_mod + other_mods;
}

 /*
 * @brief Calculate basic melee attack bonus (e.g. monster / trap etc)
 */
static int8_t calc_basic_melee_attack_bonus(entity_id_t attacker)
{
    int8_t attack_bonus = 0;
    int8_t other_mods = 0;

    util_assert(entity_has_component(attacker, COMPONENT_MELEE_ATTACK));

    attack_bonus = g.melee_components[attacker].hit_mod;
    /* TODO: Other effects (buffs, conditions)
    other_mods = effects_to_damage_bonus(attacker);
    */        

    return attack_bonus + other_mods;
}

/*
 * @brief determine attack result based on attack roll and target AC
 */
static attack_result_t resolve_attack(attack_roll_t roll, entity_id_t target)
{
    int8_t ac = g.destructable_components[target].ac;

    if (roll.d20 == 1)
        return ATTACK_MISS;

    if (roll.d20 == 20)
        return ATTACK_CRITICAL;

    if (roll.total >= ac)
        return ATTACK_HIT;

    return ATTACK_MISS;
}


/*
 * @brief Calculate melee damgage roll
 */
static int8_t roll_melee_damage(entity_id_t attacker, bool_t is_critical)
{
    int8_t damage;
    
    if (entity_has_component(attacker, COMPONENT_PLAYER))
    {
        damage = calc_player_melee_damage_roll(attacker, is_critical);
    }
    else if (entity_has_component(attacker, COMPONENT_MELEE_ATTACK))
    {
        damage = calc_basic_melee_damage_roll(attacker, is_critical);
    }
    else
    {
        util_abort("Entity cannot deal melee damage");
        return 0;
    }

    return damage < 0 ? 0 : damage ;
}


static int8_t calc_player_melee_damage_roll(entity_id_t attacker,bool_t is_critical)
{
    int8_t dice_roll = 0;
    int8_t bonus = 0;
    int8_t ability_mod = 0;
    int8_t other_mods = 0;
    entity_id_t melee_source;

    /* Determine melee source entity, attacker if unarmed / natural attack or weapon entity if a melee weapon is being wielded */
    melee_source = get_melee_source(attacker);

    dice_roll = roll_damage_dice(g.melee_components[melee_source].damage_roll, is_critical);

    bonus = g.melee_components[melee_source].damage_mod;

    // ability_mod = modifiers[g.stats_components[attacker].str];  
    ability_mod = system_stats_get_stat_mod(attacker, STAT_STR);              

    if (wielding_melee_weapon(attacker))
    {
        /* TODO: If using a finesse weapon use DEX mod if greater than STR mod */
        // ability_mod = modifiers[g.stats_components[attacker].str];        
    }

    /* TODO: calculate other effects (buffs, rage etc)*/
    /* other_mods = effects_damage_bonus(attacker); */


    /*
    text_printf(&g.msg_win, "Dice roll:%d", dice_roll);
    text_printf(&g.msg_win, "Bonus:%d", dice_roll);
    text_printf(&g.msg_win, "Ability mod:%d", ability_mod);
    text_printf(&g.msg_win, "Other mods:%d", other_mods);
    */

    return dice_roll + bonus + ability_mod + other_mods;
}

/*
 * @brief calculate basic melee damage (monster/trap etc)
 */
static int8_t calc_basic_melee_damage_roll(entity_id_t attacker, bool_t is_critical)
{
    int8_t dice_roll = 0;
    int8_t other_mods = 0;

    dice_roll = roll_damage_dice(g.melee_components[attacker].damage_roll, is_critical);

    /* NB monster modifiers already baked in */

    /* TODO: Other effects (buffs, rage, etc.) */
    /* other_mods = effects_damage_bonus(attacker); */

    return dice_roll + other_mods;
}

 /*
  * @brief returns true if the actor is wielding a melee weapon
  */
 static bool_t wielding_melee_weapon(entity_id_t actor)
 {
    entity_id_t weapon; 

    if (entity_has_component(actor, COMPONENT_SLOTS))
    {
        weapon = g.slots[SLOT_HANDS];
        return (weapon != ENTITY_ID_INVALID && entity_has_component(weapon, COMPONENT_MELEE_ATTACK));
    }
    return 0;
 }

 /*
  * @brief returns the melee source of an attack 
  */
static entity_id_t get_melee_source(entity_id_t attacker)
{
    if (wielding_melee_weapon(attacker))
        return g.slots[SLOT_HANDS];
    return attacker;
}

/*
 * @brief rolls a damage die and optionally doubles it for critical
 */
static uint8_t roll_damage_dice(dice_roll_t dice, bool_t crit)
{
    uint8_t r = game_roll_dice(dice);
    if (crit)
        r += game_roll_dice(dice);
    return r;
}
