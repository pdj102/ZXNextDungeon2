/**
 * @file item_system.c
 * @author Paul Johnson
 * @brief Items are physical objects in game world.
 */

#include "item_system.h"

#include "ecs/components/components.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/name_comp.h"

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
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = EQUIPPABLE_FINGER,
    /* Wands */
    /* Light sources */
    /* Keys */    
    [ITEM_KEY] = EQUIPPABLE_NONE
};

const name_id_t item_name_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = NAME_NONE,
    /* Melee weapons */
    [ITEM_CLUB] = NAME_CLUB,
    [ITEM_SHORT_SWORD] = NAME_SHORT_SWORD,
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = NAME_LEATHER_ARMOUR,
    /* Shields */
    [ITEM_SHIELD] = NAME_SHIELD,
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = NAME_POTION_OF_HEALING,
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = NAME_BREAD,
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = NAME_RING_OF_STRENGTH,
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = NAME_KEY
};

const attack_comp_t melee_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .attack_type = ATTACK_KIND_NONE },
    /* Melee weapons */
    [ITEM_CLUB] = { .attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    [ITEM_SHORT_SWORD] = { .attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D6, .damage_kind = DAMAGE_PIERCING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .attack_type = ATTACK_KIND_NONE },
    /* Shields */
    [ITEM_SHIELD] = { .attack_type = ATTACK_KIND_NONE },
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = { .attack_type = ATTACK_KIND_NONE },
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .attack_type = ATTACK_KIND_NONE },
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = { .attack_type = ATTACK_KIND_NONE},
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .attack_type = ATTACK_KIND_NONE },
};

const renderable_comp_t renderable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = { .tile = {' ', 0}},
    /* Melee weapons */
    [ITEM_CLUB] = { .tile = { 's', 0}},
    [ITEM_SHORT_SWORD] = { .tile = { 's', PALETTE_WHITE}},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .tile = { 'a', PALETTE_BROWN}},
    /* Shields */
    [ITEM_SHIELD] = { .tile = { 'a', 0}},
    /* Potions */
    [ITEM_POTION_OF_HEALING] = { .tile = { 'p', PALETTE_BLUE}},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .tile = { '%', 0}},
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = { .tile = { 'r', PALETTE_ORANGE}},
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
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = 0,
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = 0
};

const effect_comp_t effect_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .kind = EFFECT_NONE},
    /* Melee weapons */
    [ITEM_CLUB] = { .kind = EFFECT_NONE},
    [ITEM_SHORT_SWORD] = { .kind = EFFECT_NONE},
    /* Ranged weapons*/
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .kind = EFFECT_NONE},
    /* Shields */
    [ITEM_SHIELD] = { .kind = EFFECT_NONE},
    /* Ammo */
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = { .kind = EFFECT_NONE},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .kind = EFFECT_HEAL, .magnitude = 5, .duration = 0, .attribute = ATTRIBUTE_CUR_HP, .triggers = TRIGGER_ON_CONSUMED},
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = { .kind = EFFECT_STAT_MODIFIER, .magnitude = 2, .duration = 0xFF, .attribute = ATTRIBUTE_STR, .triggers = TRIGGER_ON_EQUIPPED},
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .kind = EFFECT_NONE},
};

/***************************************************
 * private function prototypes
 ****************************************************/
static void add_item(entity_id_t entity, item_kind_t kind, uint8_t quantity);
static void add_equippable(entity_id_t entity, equippable_slot_t slot);
static void melee_add(entity_id_t entity, const attack_comp_t *attack);
static void ranged_add(entity_id_t entity, const attack_comp_t *attack);
static void add_effect(entity_id_t entity, const effect_comp_t *effect);
static void add_name(entity_id_t entity, name_id_t name);

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
    add_item(id, kind, quantity);
    
    /* Add equippable component */
    add_equippable(id, equippable_base[kind]);

    /* Add renderable component  */
    entity_set_component(id, COMPONENT_RENDERABLE);
    g.renderable_components[id].tile = renderable_base[kind].tile;    

    /* If item has a melee attack e.g. swords*/
    if (melee_base[kind].attack_type == ATTACK_KIND_MELEE)
    {
        melee_add(id, &melee_base[kind]);
    }

    /* If item has an effect e.g. bread restores health*/
    if (effect_base[kind].kind != EFFECT_NONE)
    {
        add_effect(id, &effect_base[kind]);
    }

    /* If item is consumable add consumable component e.g. bread, potions*/
    if (consumable_base[kind] == 1)
    {
        entity_set_component(id, COMPONENT_CONSUMABLE);
    }

    /* All items have a name component*/
    add_name(id, item_name_base[kind]);

    return id;
}

/***************************************************
 * private functions
 ****************************************************/
static void add_item(entity_id_t entity, item_kind_t kind, uint8_t quantity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_ITEM)); /* entity must not have item component */
    util_assert(kind < ITEM_KIND_COUNT);
    util_assert(quantity > 0);

    g.item_components[entity].kind = kind; /* set item kind */
    g.item_components[entity].quantity = quantity; /* set quantity */

    entity_set_component(entity, COMPONENT_ITEM); /* set entity item component mask */
}

static void add_equippable(entity_id_t entity, equippable_slot_t slot)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EQUIPPABLE)); /* entity must not have equippable component */

    g.equippable_components[entity].slot = slot; 

    entity_set_component(entity, COMPONENT_EQUIPPABLE); /* set entity equippable component mask */
}

static void melee_add(entity_id_t entity, const attack_comp_t *attack)
{
    g.melee_components[entity].damage_kind = attack->damage_kind;
    g.melee_components[entity].damage_roll = attack->damage_roll;
    g.melee_components[entity].damage_mod = attack->damage_mod;
    g.melee_components[entity].hit_mod = attack->hit_mod;
    g.melee_components[entity].range = attack->range;
}

static void ranged_add(entity_id_t entity, const attack_comp_t *attack)
{
    g.melee_components[entity].damage_kind = attack->damage_kind;
    g.melee_components[entity].damage_roll = attack->damage_roll;
    g.melee_components[entity].damage_mod = attack->damage_mod;
    g.melee_components[entity].hit_mod = attack->hit_mod;
    g.melee_components[entity].range = attack->range;
}

static void add_effect(entity_id_t entity, const effect_comp_t *effect)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EFFECT)); 

    g.effect_components[entity].kind = effect->kind;
    g.effect_components[entity].magnitude = effect->magnitude;
    g.effect_components[entity].duration = effect->duration;
    g.effect_components[entity].attribute = effect->attribute;
    g.effect_components[entity].triggers = effect->triggers;

    entity_set_component(entity, COMPONENT_EFFECT); /* set entity effect component mask */
}

static void add_name(entity_id_t entity, name_id_t name)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_NAME));

    g.name_components[entity] = name; 

    entity_set_component(entity, COMPONENT_NAME);
}