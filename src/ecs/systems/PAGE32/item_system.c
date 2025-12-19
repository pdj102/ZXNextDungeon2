/**
 * @file item_system.c
 * @author Paul Johnson
 * @brief Items are physical objects in game world.
 */

#include "item_system.h"

#include "ecs/components/components.h"
#include "ecs/components/PAGE50/effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"


#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/
const equippable_slot_t equippable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = EQUIPPABLE_NONE,
    /* Melee weapons */
    [ITEM_CLUB] = EQUIPPABLE_HANDS,
    [ITEM_SHORT_SWORD] = EQUIPPABLE_HANDS,
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = EQUIPPABLE_BODY,
    /* Shields */
    [ITEM_SHIELD] = EQUIPPABLE_SHIELD,
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = EQUIPPABLE_NONE,
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = EQUIPPABLE_NONE,
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */    
    [ITEM_KEY] = EQUIPPABLE_NONE
};

const char *name_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = "NONE",
    /* Melee weapons */
    [ITEM_CLUB] = "club",
    [ITEM_SHORT_SWORD] = "short sword",
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = "leather armour",
    /* Shields */
    [ITEM_SHIELD] = "shield",
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = "potion of healing",
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = "bread",
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = "key"
};

const attack_comp_t melee_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* Melee weapons */
    [ITEM_CLUB] = { .attack_type = ATTACK_MELEE, .damage_roll = DICE_1D4, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    [ITEM_SHORT_SWORD] = { .attack_type = ATTACK_MELEE, .damage_roll = DICE_1D6, .damage_type = DAMAGE_PIERCING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* Shields */
    [ITEM_SHIELD] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
};

const renderable_comp_t renderable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = { .tile = {' ', 0}},
    /* Melee weapons */
    [ITEM_CLUB] = { .tile = { 's', 0}},
    [ITEM_SHORT_SWORD] = { .tile = { 's', 0}},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .tile = { 'a', 0}},
    /* Shields */
    [ITEM_SHIELD] = { .tile = { 'a', 0}},
    /* Potions */
    [ITEM_POTION_OF_HEALING] = { .tile = { 'p', 0}},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .tile = { '%', 0}},
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .tile = { 'k', 0}}
};

const uint8_t consumable_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = 0,
    /* Melee weapons */
    [ITEM_CLUB] = 0, 
    [ITEM_SHORT_SWORD] = 0,
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = 0,
    /* Shields */
    [ITEM_SHIELD] = 0,
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = 1,
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = 1,
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = 0
};

const effect_comp_t effect_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    /* Melee weapons */
    [ITEM_CLUB] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    [ITEM_SHORT_SWORD] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    /* Shields */
    [ITEM_SHIELD] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = { .type = EFFECT_NONE, .value = 0, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .type = EFFECT_RESTORE_HP, .value = 5, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_CONSUMED},
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .type = EFFECT_RESTORE_HP, .value = 5, .duration = 0, .stat = STAT_NONE, .status = 0, .trigger = TRIGGER_NONE},
};

/***************************************************
 * public functions
 ***************************************************/

 void item_system_init(void)
 {

 }

entity_id_t item_system_create(item_kind_t kind, uint8_t quantity)
{
    entity_id_t id = entity_create(); 

    if (id == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;

    /* Add item component */
    comp_item_add(id, kind, quantity);
    
    /* Add equippable component */
    comp_equippable_add(id, equippable_base[kind]);

    /* Add renderable component  */
    comp_renderable_add(id, renderable_base[kind].tile);

    /* If item has a melee attack and melee component e.g. swords*/
    if (melee_base[kind].attack_type == ATTACK_MELEE)
    {
        comp_melee_add(id, melee_base[kind]);
    }

    /* If item has an effect attack and effect component e.g. bread restores health*/
    if (effect_base[kind].type != EFFECT_NONE)
    {
        comp_effect_add(id, effect_base[kind]);
    }    

    /* If item is consumable add consumable component e.g. bread, potions*/
    if (consumable_base[kind] == 1)
    {
        comp_consumable_add(id);
    }    

    return id;
}

void item_system_print_name(text_window_t *win, item_kind_t kind)
{
    text_print_string(win, name_base[kind]);
}
