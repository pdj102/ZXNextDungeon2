/**
 * @file equipment_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "equipment_system.h"

#include "ecs/components/item_comp.h"

#include "game/global_state.h"

#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const equipable_slot_t equipable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = EQUIPABLE_NONE,
    /* Melee weapons */
    [ITEM_CLUB] = EQUIPABLE_HANDS,
    [ITEM_SHORT_SWORD] = EQUIPABLE_HANDS,
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = EQUIPABLE_BODY,
    /* Shields */
    [ITEM_SHIELD] = EQUIPABLE_SHIELD,
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = EQUIPABLE_NONE,
    /* Scrolls */
    /* Food and drink */
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */    
    [ITEM_KEY] = EQUIPABLE_NONE
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
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = "key"
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
    /* Wearable */
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .tile = { 'k', 0}}
};

/***************************************************
 * public functions
 ***************************************************/

 void equipment_system_init(void)
 {

 }

entity_id_t equipment_system_create(item_kind_t kind, uint8_t quantity)
{
    zxnext_tile_t tile; 

    entity_id_t id = entity_create(); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add item component */
    if (item_add(id, kind, quantity) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add equippable component */
    if (equipable_add(id, equipable_base[kind]) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }    

    /* Add renderable component  */
    if(renderable_add(id, renderable_base[kind].tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

void equipment_system_print_name(text_window_t *win, item_kind_t kind)
{
    text_print_string(win, name_base[kind]);
}
