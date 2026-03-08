/**
 * @file combat_system.c
 * @author Paul Johnson
 * @brief combat system for ECS

 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE54/combat_system.h"

#include <stdio.h>

#include "ecs/entity.h"

#include "ecs/components/components.h"
#include "ecs/components/attack_comp.h"
#include "ecs/components/stackable_comp.h"

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

typedef struct
{
    entity_id_t attacker;
    entity_id_t target;

    attack_kind_t kind;

    entity_id_t weapon;
    entity_id_t ammo;

    attack_comp_t *weapon_comp;

    int8_t attack_bonus;
    int8_t damage_bonus;    

    attack_roll_t roll;
    attack_result_t result;

    int8_t final_damage;
    damage_flag_t damage_type;
} attack_ctx_t;

/***************************************************
 * private function prototypes
 ***************************************************/

static bool attack_ctx_init(attack_ctx_t *c, entity_id_t attacker, entity_id_t target, attack_kind_t kind);
static void attack_ctx_roll(attack_ctx_t *c);
static void attack_ctx_resolve(attack_ctx_t *c);
static void attack_ctx_apply(attack_ctx_t *c);

static bool resolve_weapon(attack_ctx_t *c);
static bool resolve_ammo(attack_ctx_t *c);

static int8_t calc_player_attack_bonus(attack_ctx_t *c);
static int8_t calc_nonplayer_attack_bonus(attack_ctx_t *c);
static int8_t calc_player_damage_bonus(attack_ctx_t *c);
static int8_t calc_nonplayer_damage_bonus(attack_ctx_t *c);

static void print_ctx(attack_ctx_t *c);

static bool ammo_is_compatible(entity_id_t weapon, entity_id_t ammo);
static int8_t roll_damage_dice(dice_kind_t dice, bool critical);

/***************************************************
 * public functions
 ***************************************************/
void combat_system_init(void)
{
}

bool combat_system_try_attack(entity_id_t attacker,
                              entity_id_t target,
                              attack_kind_t kind)
{
    attack_ctx_t ctx = {0};

    if (!attack_ctx_init(&ctx, attacker, target, kind))
    {
        text_printf(&g.msg_win, "\nAttack init fail ");
        print_ctx(&ctx);
        return false;
    }
    attack_ctx_resolve(&ctx);
    attack_ctx_apply(&ctx);

    return ctx.result != ATTACK_MISS;
}

uint8_t combat_system_attack_range(entity_id_t attacker, attack_kind_t kind)
{
    attack_ctx_t ctx = {0};

    ctx.attacker = attacker;
    ctx.kind     = kind;

    if (resolve_weapon(&ctx))
    {
        return ctx.weapon_comp->range;
    }

    return 0;   /* No weapon */
}


 /***************************************************
 * private functions
 ***************************************************/

static bool attack_ctx_init(attack_ctx_t *c,
                            entity_id_t attacker,
                            entity_id_t target,
                            attack_kind_t kind)
{
    c->attacker = attacker;
    c->target   = target;
    c->kind     = kind;

    if (!entity_has_component(attacker, COMPONENT_LOCATION)) return false;
    if (!entity_has_component(target, COMPONENT_LOCATION))   return false;
    if (!entity_has_component(target, COMPONENT_DESTRUCTIBLE)) return false;

    if (!resolve_weapon(c))
        return false; /* No weapon */

    if (!in_range(g.location_components[attacker].coord,
                  g.location_components[target].coord,
                  c->weapon_comp->range))
        return false;

    if (!resolve_ammo(c))
        return false; /* No valid ammo */

    c->attack_bonus = entity_has_component(c->attacker, COMPONENT_PLAYER)
        ? calc_player_attack_bonus(c)
        : calc_nonplayer_attack_bonus(c);

    c->damage_bonus = entity_has_component(c->attacker, COMPONENT_PLAYER)
        ? calc_player_damage_bonus(c)
        : calc_nonplayer_damage_bonus(c);

    return true;
}

static void print_ctx(attack_ctx_t *c)
{
    text_printf(&g.msg_win, "\nAttacker:%d Target:%d Kind:%d Weapon:%d Ammo:%d AtkBns:%d, DmgBns:%d, Roll:%d, Dmg:%d, DmgT:%d", c->attacker, c->target, c->kind, c->weapon, c->ammo, c->attack_bonus, c->damage_bonus, c->roll, c->final_damage, c->damage_type);
}

static void attack_ctx_apply(attack_ctx_t *c)
{
    event_t event = { .source = c->attacker,
                      .target = c->target,
                      .value  = 1 };

    if (c->result == ATTACK_CRITICAL)
        event.type = EVENT_ATTACKED_AND_CRITICAL;
    else if (c->result == ATTACK_HIT)
        event.type = EVENT_ATTACKED;
    else
        event.type = EVENT_ATTACKED_AND_MISSED;

    system_event_emit(&event);

    if (c->kind == ATTACK_KIND_RANGED && c->ammo != ENTITY_ID_INVALID)
        stackable_consume_or_destroy(c->ammo);

    if (c->result == ATTACK_MISS)
        return;

    system_damage_try_take_damage(
        c->target,
        c->attacker,
        c->final_damage,
        c->damage_type
    );
}

static void attack_ctx_roll(attack_ctx_t *c)
{
    c->roll.d20   = dice_roll(DICE_1D20);
    c->roll.total = c->roll.d20 + c->attack_bonus;
    if (c->roll.total < 1) c->roll.total = 1;
}


/*
 * @details Calculate player attack bonus
 *
 * Attack bonus = 
 *  ability modifier (strength or dexterity if finesse weapon and higher) +
 *  proficency bonus (if proficient with weapon) +
 *  weapon to hit bonus (e.g. magic weapon) +
 *  ammo to hit bonus (e.g. magic ammo)
 *  other modifiers (e.g. effects)
 */
static int8_t calc_player_attack_bonus(attack_ctx_t *c)
{
    int8_t ability;
    int8_t proficiency;
    int8_t weapon_to_hit;
    int8_t ammo_to_hit;
    int8_t other;
    
    ability = system_stats_get_stat_modifier(
                        c->attacker,
                        (c->kind == ATTACK_KIND_MELEE) ? STAT_STR : STAT_DEX);

    /* TODO finesse weapons e.g. 
    if (c->kind == ATTACK_KIND_MELEE && c->weapon_comp->flags & WEAPON_FINESSE)
        ability = max(STR_mod, DEX_mod);
    */


    proficiency = (int8_t)g.player.proficiency_bonus;

    weapon_to_hit = c->weapon_comp->hit_mod;

    if (c->ammo != ENTITY_ID_INVALID)
    {
        // TODO ammo_to_hit = g.ammo_components[c->ammo].hit_mod;
        ammo_to_hit = 0;
    }
    else
    {
        ammo_to_hit = 0;
    }

    // TODO other to hit
    other = 0;

    return ability + proficiency + weapon_to_hit + ammo_to_hit + other;
}

/*
 * @details Calculate non player attack bonus
 *
 * Attack bonus = 
 *  other modifiers (e.g. effects)
 */
static int8_t calc_nonplayer_attack_bonus(attack_ctx_t *c)
{
    /* TODO other modifiers */

    return c->weapon_comp->hit_mod;
}

/*
 * @details Calculate player damage bonus
 *
 * Damage bonus = 
 *  ability modifier (strength or dexterity if finesse weapon and higher) +
 *  weapon damage bonus (e.g. magic weapon) +
 *  ammo damage bonus (e.g. magic ammo)
 *  other modifiers (e.g. effects)
 */
static int8_t calc_player_damage_bonus(attack_ctx_t *c)
{
    int8_t ability;
    int8_t weapon_to_damage;
    int8_t ammo_to_damage;
    int8_t other;
    
    ability = system_stats_get_stat_modifier(
                        c->attacker,
                        (c->kind == ATTACK_KIND_MELEE) ? STAT_STR : STAT_DEX);

    weapon_to_damage = c->weapon_comp->damage_mod;

    if (c->ammo != ENTITY_ID_INVALID)
    {
        ammo_to_damage  = g.ammo_components[c->ammo].damage_mod;
    }
    else
    {
        ammo_to_damage = 0;
    }

    // TODO other to hit
    other = 0;

    return ability + weapon_to_damage + ammo_to_damage + other;    
}

/*
 * @details Calculate non player damage bonus
 *
 * Damage bonus = 
 *  other modifiers (e.g. effects)
 */
static int8_t calc_nonplayer_damage_bonus(attack_ctx_t *c)
{
    /* TODO other modifiers */

    return c->weapon_comp->damage_mod;
}

static void attack_ctx_resolve(attack_ctx_t *c)
{
    int8_t ac;

    /* Roll 1d20*/
    attack_ctx_roll(c);

    /* Determine attack roll success or failure */
    ac = g.destructible_components[c->target].ac;

    if (c->roll.d20 == 1)
        c->result = ATTACK_MISS;
    else if (c->roll.d20 == 20)
        c->result = ATTACK_CRITICAL;
    else if (c->roll.total >= ac)
        c->result = ATTACK_HIT;

    if (c->result == ATTACK_MISS)
        return;

    /* Roll damage */
    int8_t dice = c->weapon_comp->damage_roll;

    if (c->ammo != ENTITY_ID_INVALID)
    {
        ammo_comp_t *a = &g.ammo_components[c->ammo];
        dice  = a->damage_roll;
    }
    int8_t dmg = roll_damage_dice(dice, c->result == ATTACK_CRITICAL);

    /* Calculate final damage result*/
    c->final_damage = dmg + c->damage_bonus;
    if (c->final_damage < 0) c->final_damage = 0;

    #ifndef NDEBUG
        print_ctx(c);
    #endif
}

/*
 * @brief Determine source of attack e.g. equipped weapon or native attack 
 *
 * If attacker has slots and equipped weapon use it
 * Else if attacker has (melee/ranged) attack component, use it
 * Else no source of attack
 */
static bool resolve_weapon(attack_ctx_t *c)
{
    c->weapon = ENTITY_ID_INVALID;
    c->weapon_comp = NULL;

    if (entity_has_component(c->attacker, COMPONENT_SLOTS))
    {
        if (c->kind == ATTACK_KIND_MELEE)
        {
            c->weapon = g.slots[SLOT_HANDS];
            if (c->weapon != ENTITY_ID_INVALID)
            {
                c->weapon_comp = &g.melee_components[c->weapon];
                c->damage_type = c->weapon_comp->damage_kind;
                return true; /* Attacker is wielding melee weapon */
            }
        }
        else if (c->kind == ATTACK_KIND_RANGED)
        {
            c->weapon = g.slots[SLOT_RANGED];
            if (c->weapon != ENTITY_ID_INVALID)
            {
                c->weapon_comp = &g.ranged_components[c->weapon];
                c->damage_type = c->weapon_comp->damage_kind;
                return true; /* Attacker is wielding ranged weapon */
            }
        }
    }

    if (c->kind == ATTACK_KIND_MELEE && entity_has_component(c->attacker, COMPONENT_MELEE_ATTACK))
    {
        c->weapon = c->attacker; 
        c->weapon_comp = &g.melee_components[c->weapon];
        c->damage_type = c->weapon_comp->damage_kind;
        return true; /* source of attack is the attacker */
    }

    if (c->kind == ATTACK_KIND_RANGED && entity_has_component(c->attacker, COMPONENT_RANGED_ATTACK))
    {
        c->weapon = c->attacker; 
        c->weapon_comp = &g.ranged_components[c->weapon];
        c->damage_type = c->weapon_comp->damage_kind;
        return true; /* source of attack is the attacker */
    }

    return false; /* Unable to resolve source of attack */
}

/*
 * If attacker has slots, only slot ammo allowed
 * Else if attacker has ammo component, use it
 */
static bool resolve_ammo(attack_ctx_t *c)
{
    c->ammo = ENTITY_ID_INVALID;

    if (c->kind != ATTACK_KIND_RANGED) return true; /* only ranged attacks have ammo */

    if (entity_has_component(c->attacker, COMPONENT_SLOTS))
    {
        c->ammo = g.slots[SLOT_AMMO];
    }
    else if (entity_has_component(c->attacker, COMPONENT_AMMO))
    {
        c->ammo = c->attacker;
    }

    if (c->ammo == ENTITY_ID_INVALID) return false; /* no ammo source */

    if (!ammo_is_compatible(c->weapon, c->ammo))
        return false; /* Ammo is not compatible with weapon */

    /* Change damage type to the ammo */
    c->damage_type = g.ammo_components[c->ammo].damage_kind;

    return true; /* Successfully resolved ammo source */
}

static bool ammo_is_compatible(entity_id_t weapon, entity_id_t ammo)
{
    attack_comp_t *w = &g.ranged_components[weapon];
    ammo_comp_t   *a = &g.ammo_components[ammo];

    return (w->allowed_ammo & a->ammo_type) != 0;
}


static int8_t roll_damage_dice(dice_kind_t dice, bool critical)
{
    int8_t r = dice_roll(dice);
    if (critical)
        r += dice_roll(dice);
    return r;
}


/* ********************************************************************************************************* */


