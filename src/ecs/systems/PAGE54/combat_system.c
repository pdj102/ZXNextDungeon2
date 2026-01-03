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
#include "ecs/components/attack_comp.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/dice.h"
#include "game/spatial.h"
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
static entity_id_t get_attack_source(entity_id_t attacker, attack_kind_t kind);
static attack_roll_t roll_attack(entity_id_t attacker, attack_kind_t kind);
static int8_t calc_player_attack_bonus(entity_id_t attacker, attack_kind_t kind);
static int8_t calc_nonplayer_attack_bonus(entity_id_t attacker, attack_kind_t kind);
static attack_result_t resolve_attack(attack_roll_t roll, entity_id_t target);
static entity_id_t get_equipped_weapon(entity_id_t actor, attack_kind_t kind);
static int8_t get_attack_base_bonus(entity_id_t source, attack_kind_t kind);
static stat_kind_t get_attack_ability(attack_kind_t kind);
static int8_t roll_attack_damage(entity_id_t attacker, attack_kind_t kind, bool critical);
static int8_t roll_damage_dice(dice_kind_t dice, bool critical);
static damage_flag_t get_damage_type(entity_id_t attacker, attack_kind_t kind);
static int8_t calc_player_damage(entity_id_t attacker, attack_kind_t kind, bool critical);
static int8_t calc_nonplayer_damage(entity_id_t attacker, attack_kind_t kind, bool critical);
static attack_comp_t* get_attack_component(entity_id_t source, attack_kind_t kind);

/***************************************************
 * public functions
 ***************************************************/
void combat_system_init(void)
{
}

bool combat_system_try_attack(entity_id_t attacker, entity_id_t target, attack_kind_t kind)
{
    attack_roll_t roll;
    entity_id_t source;
    attack_comp_t *comp;
    event_t event = { .source = attacker, .target = target, .value = 1 };
    attack_result_t result;

    /* determine the entity that is the source of the attack e.g. weapon or natural */
    source = get_attack_source(attacker, kind);

    if ((kind == ATTACK_KIND_MELEE) && !entity_has_component(source, COMPONENT_MELEE_ATTACK))
        return false;
    if ((kind == ATTACK_KIND_RANGED) && !entity_has_component(source, COMPONENT_RANGED_ATTACK))
        return false;
    if (!entity_has_component(attacker, COMPONENT_LOCATION)) return false;
    if (!entity_has_component(target, COMPONENT_LOCATION)) return false;
    if (!entity_has_component(target, COMPONENT_DESTRUCTIBLE)) return false;

    /* get the attack component of the source */
    comp = get_attack_component(source, kind);

    /* check target is in range */
    if (!in_range(g.location_components[attacker].coord, g.location_components[target].coord, comp->range))
        return false;

    /* get the roll of the attack */
    roll = roll_attack(attacker, kind);

    text_printf(&g.msg_win, "Attack roll:%d", roll);
    text_printf(&g.msg_win, "Weapon:%d ", get_equipped_weapon(attacker, kind));
    text_printf(&g.msg_win, "Source:%d ", source);
    text_printf(&g.msg_win, "Damage kind:%d ", comp->damage_kind);
    text_printf(&g.msg_win, "Dice:%d ", comp->damage_roll);

    result = resolve_attack(roll, target);

    switch (result)
    {
        case ATTACK_CRITICAL:
            event.type = EVENT_ATTACKED_AND_CRITICAL;
            break;
        case ATTACK_HIT:
            event.type = EVENT_ATTACKED;
            break;
        case ATTACK_MISS:
            event.type = EVENT_ATTACKED_AND_MISSED;
            break;
    }

    system_event_emit(&event);

    if (result == ATTACK_MISS)
        return false;

    system_damage_try_take_damage(
        target,
        roll_attack_damage(attacker, kind, result == ATTACK_CRITICAL),
        get_damage_type(attacker, kind)
    );

    return true;
}

uint8_t combat_system_attack_range(entity_id_t attacker, attack_kind_t kind)
{
    entity_id_t source;
    attack_comp_t *comp;
    
    /* determine the entity that is the source of the attack e.g. weapon or natural */
    source = get_attack_source(attacker, kind);

    text_printf(&g.msg_win, "\nAttacker %d", attacker);
    system_name_print(&g.msg_win, g.name_components[attacker]);

    text_printf(&g.msg_win, "\nWeapon source %d", source);
    system_name_print(&g.msg_win, g.name_components[source]);

    if ((kind == ATTACK_KIND_MELEE) && !entity_has_component(source, COMPONENT_MELEE_ATTACK))
        return 0;
    if ((kind == ATTACK_KIND_RANGED) && !entity_has_component(source, COMPONENT_RANGED_ATTACK))
        return 0;
    if (!entity_has_component(attacker, COMPONENT_LOCATION)) return 0;

    /* get the attack component of the source */
    comp = get_attack_component(source, kind);

    return comp->range;
}


 /***************************************************
 * private functions
 ***************************************************/
static entity_id_t get_attack_source(entity_id_t attacker, attack_kind_t kind)
{
    entity_id_t weapon = get_equipped_weapon(attacker, kind);
    return (weapon != ENTITY_ID_INVALID) ? weapon : attacker;
}

static attack_roll_t roll_attack(entity_id_t attacker, attack_kind_t kind)
{
    attack_roll_t roll;
    int8_t bonus = 0;

    roll.d20 = dice_roll(DICE_1D20);

    if (entity_has_component(attacker, COMPONENT_PLAYER)) {
        bonus = calc_player_attack_bonus(attacker, kind);
    }
    else 
    {
        bonus = calc_nonplayer_attack_bonus(attacker, kind);
    }

    roll.total = roll.d20 + bonus;
    if (roll.total < 1) roll.total = 1;

    return roll;
}

/*
 * @details Calculate player attack bonus
 *
 * Attack bonus = 
 *  Ability modifier (strength or dexterity if finesse weapon and higher) +
 *  proficency bonus (if proficient with weapon) +
 *  weapon bonus (e.g. magic weapon) +
 *  other modifiers (e.g. effects)
 */
static int8_t calc_player_attack_bonus(entity_id_t attacker, attack_kind_t kind)
{
    util_assert(entity_has_component(attacker, COMPONENT_PLAYER));
    util_assert(entity_has_component(attacker, COMPONENT_STATS));

    int8_t base_bonus;
    int8_t ability_mod;
    int8_t proficiency_mod = 0;
    int8_t other_mods = 0;

    entity_id_t source = get_attack_source(attacker, kind);
    
    base_bonus  = get_attack_base_bonus(source, kind);
    ability_mod = system_stats_get_stat_modifier(attacker, get_attack_ability(kind));

    /* TODO proficiency system */
    /* TODO buffs / effects */

    return base_bonus + ability_mod + proficiency_mod + other_mods;
}

static int8_t calc_nonplayer_attack_bonus(entity_id_t attacker, attack_kind_t kind)
{
    int8_t base_bonus;
    int8_t other_mods = 0;

    base_bonus  = get_attack_base_bonus(attacker, kind);

    /* TODO buffs / effects */

    return base_bonus + other_mods;
}

/*
 * @brief determine attack result based on attack roll and target AC
 */
static attack_result_t resolve_attack(attack_roll_t roll, entity_id_t target)
{
    int8_t ac = g.destructible_components[target].ac;

    if (roll.d20 == 1)
        return ATTACK_MISS;

    if (roll.d20 == 20)
        return ATTACK_CRITICAL;

    if (roll.total >= ac)
        return ATTACK_HIT;

    return ATTACK_MISS;
}

static entity_id_t get_equipped_weapon(entity_id_t actor, attack_kind_t kind)
{
    if (!entity_has_component(actor, COMPONENT_SLOTS))
        return ENTITY_ID_INVALID;

    entity_id_t weapon = (kind == ATTACK_KIND_MELEE)
        ? g.slots[SLOT_HANDS]
        : g.slots[SLOT_RANGED];

    if (weapon == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;

    if ((kind == ATTACK_KIND_MELEE) && (entity_has_component(weapon, COMPONENT_MELEE_ATTACK)))
        return weapon;

    if ((kind == ATTACK_KIND_RANGED) && (entity_has_component(weapon, COMPONENT_RANGED_ATTACK)))
        return weapon;

    text_printf(&g.msg_win, "  invalid weapon  ");

    return ENTITY_ID_INVALID;
}

static int8_t roll_attack_damage(entity_id_t attacker, attack_kind_t kind, bool critical)
{
    if (entity_has_component(attacker, COMPONENT_PLAYER))
        return calc_player_damage(attacker, kind, critical);
    else
        return calc_nonplayer_damage(attacker, kind, critical);
}

static attack_comp_t* get_attack_component(entity_id_t source,
                                           attack_kind_t kind)
{
    return (kind == ATTACK_KIND_MELEE)
           ? &g.melee_components[source]
           : &g.ranged_components[source];
}

static damage_flag_t get_damage_type(entity_id_t attacker, attack_kind_t kind)
 {
    entity_id_t source = get_attack_source(attacker, kind);

    attack_comp_t *comp = get_attack_component(source, kind);

    return comp->damage_kind;
}

static int8_t get_attack_base_bonus(entity_id_t source, attack_kind_t kind)
{
    attack_comp_t *comp = get_attack_component(source, kind);

    return comp->hit_mod;
}

static stat_kind_t get_attack_ability(attack_kind_t kind)
{
    return (kind == ATTACK_KIND_MELEE) ? STAT_STR : STAT_DEX;
}

static int8_t calc_player_damage(entity_id_t attacker,
                                 attack_kind_t kind,
                                 bool critical)
{
    util_assert(entity_has_component(attacker, COMPONENT_PLAYER));
    util_assert(entity_has_component(attacker, COMPONENT_STATS));

    entity_id_t source = get_attack_source(attacker, kind);

    int8_t dice;
    int8_t base_bonus;
    int8_t ability_mod;
    int8_t other_mods = 0;

    attack_comp_t *comp = get_attack_component(source, kind);

    dice = comp->damage_roll;
    base_bonus = comp->damage_mod;

    if (kind == ATTACK_KIND_MELEE)
    {
        ability_mod = system_stats_get_stat_modifier(attacker, STAT_STR);
        /* TODO finesse: use DEX if finesse weapon and DEX > STR */
    }
    else
    {
        ability_mod = system_stats_get_stat_modifier(attacker, STAT_DEX);
    }

    /* TODO: buffs, effects, conditions, enchantments */
    /* other_mods = effects_damage_bonus(attacker); */

    int8_t roll = roll_damage_dice(dice, critical);

    int8_t total = roll + base_bonus + ability_mod + other_mods;

    if (total < 0) total = 0;
    return total;
}

static int8_t calc_nonplayer_damage(entity_id_t attacker,
                                   attack_kind_t kind,
                                   bool critical)
{
    int8_t dice;
    int8_t other_mods = 0;

    if (kind == ATTACK_KIND_MELEE)
    {
        util_assert(entity_has_component(attacker, COMPONENT_MELEE_ATTACK));
        dice = g.melee_components[attacker].damage_roll;
    }
    else
    {
        util_assert(entity_has_component(attacker, COMPONENT_RANGED_ATTACK));
        dice = g.ranged_components[attacker].damage_roll;
    }

    /* TODO: buffs, rage, status effects, etc */
    /* other_mods = effects_damage_bonus(attacker); */

    int8_t total = roll_damage_dice(dice, critical) + other_mods;

    if (total < 0) total = 0;
    return total;
}



static int8_t roll_damage_dice(dice_kind_t dice, bool critical)
{
    int8_t r = dice_roll(dice);
    if (critical)
        r += dice_roll(dice);
    return r;
}


/* ********************************************************************************************************* */


