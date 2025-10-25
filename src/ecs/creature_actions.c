/**
 * @file creature_actions.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "creature_actions.h"

#include "entity.h"

#include "location_comp.h"
#include "contained_comp.h"

#include "../game/global_state.h"
#include "../core/text.h"
#include "../core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/

bool_t creature_actions_try_melee_attack(entity_id_t creature, entity_id_t target)
{
    int8_t attack_roll;
    int8_t damage_roll;

    /* entity to be attacked has creature and location component */
    util_assert(entity_has_component(target, COMPONENT_LOCATION | COMPONENT_CREATURE));
    
    /* actor has creature, contained and location */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_LOCATION));
    
    /* check target within melee attack range */

    /* try attack*/

    /* attack roll calculation = 1d20 + to_hit_bonus (which is weapon mod + ability modifer + proficiency bonus) */
    attack_roll = util_roll_dice(DICE_1D20);
    attack_roll += g.creature_components[creature].melee.to_hit;
    
    /* successful hit if attack roll is greater or equal to target's armour class */
    if (attack_roll >= g.creature_components[target].ac)
    {
        /* damage roll calculation = weapon dice roll + to_damage_bonus (which is weapon mod + ability modifer + proficiency bonus )*/
        damage_roll = util_roll_dice(g.creature_components[creature].melee.damage_roll);
        damage_roll += g.creature_components[creature].melee.to_damage;

        creature_actions_try_take_damage(target, damage_roll, g.creature_components[creature].melee.damage_type);

        text_printf(&g.msg_win, "Attack roll:%u ac: %u\n", attack_roll, g.creature_components[target].ac);
        text_printf(&g.msg_win, "Die:%u\n", g.creature_components[creature].melee.damage_roll);
        text_printf(&g.msg_win, "Damage roll:%u hp: %u\n", damage_roll, g.creature_components[target].cur_hp);
        return 1;
    }
    else
    {
        text_printf(&g.msg_win, "Attack roll:%u ac: %u\n", attack_roll, g.creature_components[target].ac);
        return 0;
    }
}

int8_t creature_actions_try_take_damage(entity_id_t creature, int8_t damage, damage_type_t type)
{
    /* if cur_hp reduced to zero or less kill creature, otherwise reduce cur_hp by damage */
    if (g.creature_components[creature].cur_hp <= damage)
    {
        g.creature_components[creature].cur_hp = 0;
        creature_actions_try_die(creature);
    }
    else
    {
        g.creature_components[creature].cur_hp -= damage;
    }
    
    return damage;
}

bool_t creature_actions_try_die(entity_id_t creature)
{
    entity_destroy(creature);

    return 1;
}

bool_t creature_actions_try_pickup(entity_id_t creature, entity_id_t item)
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

    contained_add(item, creature);

    return 1;
}

bool_t creature_actions_try_drop(entity_id_t creature, entity_id_t item)
{
    uint8_t x, y;

    /* entity to be droped has item and contained components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_CONTAINED));

    /* actor has creature, container and location components */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_CONTAINER | COMPONENT_LOCATION));

    /* check creature is holding the item */
    if (!g.contained_components[item].container == creature)
    {
        return 0;
    }

    contained_remove(item);

    x = g.location_components[creature].x;
    y = g.location_components[creature].y;

    text_printf(&g.msg_win, "Dropping %d at (%d,%d)\n", item, x, y);
    location_add(item, x, y);

    return 1;
}