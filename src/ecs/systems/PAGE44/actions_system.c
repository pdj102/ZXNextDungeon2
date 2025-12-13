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

#include "game/game.h"
#include "game/global_state.h"

#include "core/systems_dispatch.h"
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
bool_t actions_system_try_close(entity_id_t creature, entity_id_t feature)
{
    
}

bool_t actions_system_try_die(entity_id_t creature)
{
    system_event_emit(EVENT_DIED, creature, ENTITY_ID_INVALID, 0);

    entity_mark_for_destruction(creature);

    return 1;
}

bool_t actions_system_try_drop(entity_id_t actor, entity_id_t item)
{
    uint8_t x, y;

    /* item to be droped has item and contained components */
    if (!entity_has_component(item, COMPONENT_ITEM | COMPONENT_CONTAINED))
    {
        return 0;
    }
    /* actor has container and location components */
    if (!entity_has_component(item, COMPONENT_CONTAINER | COMPONENT_LOCATION))
    {
        return 0;
    }    
    /* creature is holding the item */
    if (g.contained_components[item].container != actor)
    {
        return 0;
    }

    /* TODO check not equipped */

    /* TODO implement an inventory system */

    system_container_remove_item_from(actor, item);
    
    x = g.location_components[actor].x;
    y = g.location_components[actor].y;
    location_add(item, x, y);

    system_event_emit(EVENT_DROPPED, actor, item, 0);    

    return 1;
}

bool_t actions_system_try_eat(entity_id_t actor, entity_id_t item)
{

}

bool_t actions_system_try_equip(entity_id_t actor, entity_id_t item)
{
    equip_slot_t slot = EQUIP_NONE;

    /* item to be equipped must have equipable component */
    if (!entity_has_component(item, COMPONENT_EQUIPABLE))
    {
        system_event_emit(EVENT_EQUIPPED, actor, item, 0);
        return 0;
    }
    /* actor must have equip component */
    if (!entity_has_component(actor, COMPONENT_EQUIP))
    {
        system_event_emit(EVENT_EQUIPPED, actor, item, 0);
        return 0;
    }
    /* item must not already be equipped */
    if (g.equipable_components[item].equipped_by != ENTITY_ID_INVALID)
    {
        system_event_emit(EVENT_EQUIPPED, actor, item, 0);
        return 0;
    }

    /* Identify the equip slot to use */

    switch (g.equipable_components[item].slot)
    {
        case EQUIPABLE_HEAD:
        {
            slot = EQUIP_HEAD;
            break;
        }
        case EQUIPABLE_NECK:
        {
            slot = EQUIP_NECK;
            break;
        }        
        case EQUIPABLE_BODY:
        {
            slot = EQUIP_BODY;
            break;
        }        
        case EQUIPABLE_HANDS:
        {
            slot = EQUIP_HANDS;
            break;
        }
        case EQUIPABLE_FINGER:
        {
            if (g.equip_slots[EQUIP_FINGER_LEFT] == ENTITY_ID_INVALID)
            {
                slot = EQUIP_FINGER_LEFT;
            } 
            else
            {
                slot = EQUIP_FINGER_RIGHT;
            }
            break;
        }
        case EQUIPABLE_FEET:
        {
            slot = EQUIP_FEET;
            break;
        }
        case EQUIPABLE_LEGS:
        {
            slot = EQUIP_LEGS;
            break;
        }
        case EQUIPABLE_MELEE:
        {
            slot = EQUIP_MELEE;
            break;
        }
        case EQUIPABLE_RANGED:
        {
            slot = EQUIP_RANGED;
            break;
        }
        case EQUIPABLE_AMMO:
        {
            slot = EQUIP_AMMO;
            break;
        }
        default:
        {
            system_event_emit(EVENT_EQUIPPED, actor, item, 0);
            return 0;
        }
    }

    /* Equip item*/
    g.equip_slots[slot] = item;
    g.equipable_components[item].equipped_by = actor;

    system_event_emit(EVENT_EQUIPPED, actor, item, 1);        
    
    return 1;
}

bool_t actions_system_try_pickup(entity_id_t actor, entity_id_t item)
{  
    /* item to be picked up has item and location components */
    if (!entity_has_component(item, COMPONENT_ITEM | COMPONENT_LOCATION))
    {
        return 0;
    }
    /* actor has container, location and item components */
    if (!entity_has_component(item, COMPONENT_CONTAINER | COMPONENT_LOCATION ))
    {
        return 0;
    }    
    /* actor and item are at the same location*/
    if (!location_equal(actor, item))
    {
        return 0;
    }
    /* container is not full */
    if (g.container_components[actor].count >= g.container_components[actor].capacity)
    {
        return 0;
    }    

    location_remove(item);
    system_container_place_item_in(actor, item);
    system_event_emit(EVENT_PICKED_UP, actor, item, 0);

    return 1;
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

 bool_t actions_system_try_move(entity_id_t actor, int8_t dx, int8_t dy)
 {
    uint8_t tx;
    uint8_t ty;

    tx = g.location_components[actor].x + dx;
    ty = g.location_components[actor].y + dy;

    if (map_can_enter(actor, tx, ty))
    {
        location_move(actor, tx, ty);
        return 1;
    }
    else
    {
        return 0;
    }
}

bool_t actions_system_try_open(entity_id_t actor, entity_id_t feature)
{

}

bool_t actions_system_try_quaff(entity_id_t actor, entity_id_t item)
 {

 }

bool_t actions_system_try_unequip(entity_id_t actor, entity_id_t item)
{
    /* item to be unequipped must be equipable */
    if (!entity_has_component(item, COMPONENT_EQUIPABLE))
    {
        system_event_emit(EVENT_UNEQUIPPED, actor, item, 0);
        return 0;
    }

    /* item must be equipped by the actor */
    if (g.equipable_components[item].equipped_by != actor)
    {
        system_event_emit(EVENT_UNEQUIPPED, actor, item, 0);
        return 0;
    }

    /* Iterate through equipable slots and remove item from slot if found */
    text_printf(&g.msg_win, "Item: %d", item);

    for (equip_slot_t slot = 0; slot < EQUIP_COUNT; slot++)
    {
        text_printf(&g.msg_win, "Slot: %d", g.equip_slots[slot]);
        if (g.equip_slots[slot] == item)
        {
            g.equip_slots[slot] = ENTITY_ID_INVALID;
            g.equipable_components[item].equipped_by = ENTITY_ID_INVALID;

            system_event_emit(EVENT_UNEQUIPPED, actor, item, 1);
            return 1;
        }
    }
    system_event_emit(EVENT_UNEQUIPPED, actor, item, 0);
    return 0;
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
        if (g.equip_slots[EQUIP_HANDS] != ENTITY_ID_INVALID)
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