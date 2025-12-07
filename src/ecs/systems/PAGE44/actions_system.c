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

#include "ecs/components/location_comp.h"

#include "game/global_state.h"

#include "core/systems_dispatch.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/

 const int8_t modifiers[] = { -4, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

/***************************************************
 * private function prototypes
 ***************************************************/
 int8_t calc_attack_roll(entity_id_t attacker, attack_type_t attack_type);

/***************************************************
 * public functions
 ***************************************************/
bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature)
{
    
}

bool_t actions_system_try_die(entity_id_t creature)
{
    system_event_emit(EVENT_DIED, creature, ENTITY_ID_INVALID, 0);

    entity_mark_for_destruction(creature);

    return 1;
}

bool_t actions_system_try_drop(entity_id_t creature, entity_id_t item)
{
    uint8_t x, y;

    /* entity to be droped has item and contained components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_CONTAINED));

    /* actor has creature, container and location components */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_CONTAINER | COMPONENT_LOCATION));

    /* check creature is holding the item */
    if (g.contained_components[item].container != creature)
    {
        return 0;
    }

    /* TODO check not equipped */

    system_container_remove_item_from(creature, item);
    
    x = g.location_components[creature].x;
    y = g.location_components[creature].y;
    location_add(item, x, y);

    system_event_emit(EVENT_DROPPED, creature, item, 0);    

    return 1;
}

bool_t actions_system_try_eat(entity_id_t creature, entity_id_t item)
{

}

bool_t actions_system_try_equip(entity_id_t creature, entity_id_t item)
{
    /* entity to be equipped has item and contained components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_CONTAINED));

    /* actor has creature, container and player_ctrl components */
    util_assert(entity_has_component(creature, COMPONENT_PLAYER_CTRL | COMPONENT_CONTAINER ));

    /* check creature is holding the item */
    if (g.contained_components[item].container != creature)
    {
        return 0;
    }

    switch (system_equipment_get_class(g.item_components[item].kind))
    {
        case ITEM_CLASS_MELEE:
        {
            g.player.hands = item;
            system_event_emit(EVENT_EQUIPPED, creature, item, 1);
            break;
        }
        case ITEM_CLASS_RING:
        {
            /* TODO left and rgith fingers */
            g.player.left_finger = item;
            system_event_emit(EVENT_EQUIPPED, creature, item, 1);
        }
        default:
        {
            system_event_emit(EVENT_EQUIPPED, creature, item, 0);
            return 0;
        }
    }
    return 1;
}

bool_t actions_system_try_pickup(entity_id_t creature, entity_id_t item)
{  
    /* entity to be picked up has item and location components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_LOCATION));

    /* actor has creature, container and location components */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_CONTAINER | COMPONENT_LOCATION));

    /* check creature and item are at the same location*/
    if (!location_equal(creature, item))
    {
        return 0;
    }

    location_remove(item);
    
    if (system_container_place_item_in(creature, item))
    {
        system_event_emit(EVENT_PICKED_UP, creature, item, 0);
        return 1;
    }
    else
    {
        // TODO put the item back on the map
        // location_add(item, x, y);
        return 0;
    }


}




bool_t actions_system_try_melee_attack(entity_id_t attacker, entity_id_t target)
{
    int8_t attack_roll;
    int8_t damage_roll;

    /* entity to be attacked has creature and location component */
    util_assert(entity_has_component(target, COMPONENT_LOCATION | COMPONENT_CREATURE));
    
    /* actor has creature, contained and location */
    util_assert(entity_has_component(attacker, COMPONENT_CREATURE | COMPONENT_LOCATION));
    
    /* check target within melee attack range */

    /* try attack*/

    /* attack roll */
    attack_roll = calc_attack_roll(attacker, ATTACK_MELEE);
    
    /* successful hit if attack roll is greater or equal to target's armour class */
    if (attack_roll >= g.creature_components[target].stats.ac)
    {
        /* damage roll calculation = weapon dice roll +damage_mod_bonus (which is weapon mod + ability modifer + proficiency bonus )*/
        damage_roll = util_roll_dice(g.creature_components[attacker].melee.damage_roll);
        damage_roll += g.creature_components[attacker].melee.damage_mod;

        system_event_emit(EVENT_ATTACKED, attacker, target, 1);

        actions_system_try_take_damage(target, damage_roll, g.creature_components[attacker].melee.damage_type);
        return 1;
    }
    else
    {
        system_event_emit(EVENT_ATTACKED, attacker, target, 0);
        return 0;
    }
}

int8_t actions_system_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type)
{
    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.creature_components[creature].stats.cur_hp <= damage)
    {
        g.creature_components[creature].stats.cur_hp = 0;
        actions_system_try_die(creature);
    }
    else
    {
        g.creature_components[creature].stats.cur_hp -= damage;
    }
    
    return damage;
}

 bool_t actions_system_try_move(entity_id_t entity, int8_t dx, int8_t dy)
 {
    uint8_t tx;
    uint8_t ty;

    tx = g.location_components[entity].x + dx;
    ty = g.location_components[entity].y + dy;

    if (map_can_enter(entity, tx, ty))
    {
        location_move(entity, tx, ty);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool_t actions_system_try_open(entity_id_t creature, entity_id_t feature)
{

}

bool_t actions_system_try_quaff(entity_id_t creature, entity_id_t item)
 {

 }

bool_t actions_system_try_unequip(entity_id_t creature, entity_id_t item)
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
    d20 = util_roll_dice(DICE_1D20);

    /* Is the attacker the player?*/
    if (attacker == g.player.id)
    {
        /* Calculate player attack roll */
        /* Step 2 - Choose the correct ability modifier (STR or DEX) */
        switch (attack_type)
        {
            case ATTACK_MELEE:
            ability_mod = modifiers[g.creature_components[attacker].stats.str];
            break;

            case ATTACK_RANGED:
            ability_mod = modifiers[g.creature_components[attacker].stats.dex];
            break;

            default:
            ability_mod = 0;
        }

        /* Step 3 - Choose the correct proficiency modifier */
        /* TODO */

        /* Step 4 - If using a weapon determine weapon bonus*/
        if (g.player.hands != ENTITY_ID_INVALID)
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
            attack_mod = g.creature_components[attacker].melee.hit_mod;
            break;

            case ATTACK_RANGED:
            attack_mod = g.creature_components[attacker].ranged.hit_mod;
            break;

            default:
            attack_mod = 0;
        }
        return d20 + attack_mod;
    }    
}