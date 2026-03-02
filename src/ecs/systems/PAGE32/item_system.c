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
static const equippable_slot_t equippable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = EQUIPPABLE_NONE,
    /* Melee weapons */
    [ITEM_CLUB] = EQUIPPABLE_HANDS,
    [ITEM_SHORT_SWORD] = EQUIPPABLE_HANDS,
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = EQUIPPABLE_RANGED,
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = EQUIPPABLE_BODY,
    /* Shields */
    [ITEM_SHIELD] = EQUIPPABLE_SHIELD,
    /* Ammo */
    [ITEM_ARROW] = EQUIPPABLE_AMMO,
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
    [ITEM_KEY] = EQUIPPABLE_NONE,
    /* Quest items */
    [ITEM_AMULET] = EQUIPPABLE_NONE
};

static const name_id_t item_name_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = NAME_NONE,
    /* Melee weapons */
    [ITEM_CLUB] = NAME_CLUB,
    [ITEM_SHORT_SWORD] = NAME_SHORT_SWORD,
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = NAME_SHORT_BOW,
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = NAME_LEATHER_ARMOUR,
    /* Shields */
    [ITEM_SHIELD] = NAME_SHIELD,
    /* Ammo */
    [ITEM_ARROW] = NAME_ARROW,
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
    [ITEM_KEY] = NAME_KEY,
    /* Quest items */
    [ITEM_AMULET] = NAME_AMULET
};

static const attack_comp_t melee_base[ITEM_KIND_COUNT] =
{
    [ITEM_NONE] = { .attack_type = ATTACK_KIND_NONE },
    /* Melee weapons */
    [ITEM_CLUB] = { .attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 0, .damage_mod = 0, .allowed_ammo = AMMO_NONE},
    [ITEM_SHORT_SWORD] = { .attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D6, .damage_kind = DAMAGE_PIERCING, .range = 1, .hit_mod = 0, .damage_mod = 0, .allowed_ammo = AMMO_NONE},
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = { .attack_type = ATTACK_KIND_NONE },
    /* Armour */
    [ITEM_LEATHER_ARMOUR] = { .attack_type = ATTACK_KIND_NONE },
    /* Shields */
    [ITEM_SHIELD] = { .attack_type = ATTACK_KIND_NONE },
    /* Ammo */
    [ITEM_ARROW] = { .attack_type = ATTACK_KIND_NONE },
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
    /* Quest items */
    [ITEM_AMULET] = { .attack_type = ATTACK_KIND_NONE },
};

static const attack_comp_t ranged_base[ITEM_KIND_COUNT] =
{
    [ITEM_NONE] = { .attack_type = ATTACK_KIND_NONE },
    /* Melee weapons */
    [ITEM_CLUB] = { .attack_type = ATTACK_KIND_NONE },
    [ITEM_SHORT_SWORD] = { .attack_type = ATTACK_KIND_NONE },
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = { .attack_type = ATTACK_KIND_RANGED, .damage_roll = DICE_1D6, .damage_kind = DAMAGE_PIERCING, .range = 10, .hit_mod = 0, .damage_mod = 0, .allowed_ammo = AMMO_ARROW},
    /* Armour */
    [ITEM_LEATHER_ARMOUR] = { .attack_type = ATTACK_KIND_NONE },
    /* Shields */
    [ITEM_SHIELD] = { .attack_type = ATTACK_KIND_NONE },
    /* Ammo */
    [ITEM_ARROW] = { .attack_type = ATTACK_KIND_NONE },
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
    /* Quest items */
    [ITEM_AMULET] = { .attack_type = ATTACK_KIND_NONE },
};

static const ammo_comp_t ammo_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .ammo_type = AMMO_NONE },
    /* Melee weapons */
    [ITEM_CLUB] = { .ammo_type = AMMO_NONE },
    [ITEM_SHORT_SWORD] = { .ammo_type = AMMO_NONE },
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = { .ammo_type = AMMO_NONE },
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .ammo_type = AMMO_NONE },
    /* Shields */
    [ITEM_SHIELD] = { .ammo_type = AMMO_NONE },
    /* Ammo */
    [ITEM_ARROW] = { .ammo_type = AMMO_ARROW, .damage_kind = DAMAGE_PIERCING, .damage_roll = DICE_1D6, .damage_mod = 0, .hit_mod = 0},
    /* Potions */
    [ITEM_POTION_OF_HEALING] = { .ammo_type = AMMO_NONE },
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .ammo_type = AMMO_NONE },
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = { .ammo_type = AMMO_NONE },
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .ammo_type = AMMO_NONE },
    /* Quest items */
    [ITEM_AMULET] = { .ammo_type = AMMO_NONE },
};

static const renderable_comp_t renderable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = { .tile = {' ', 0}},
    /* Melee weapons */
    [ITEM_CLUB] = { .tile = { 's', PALETTE_WHITE}},
    [ITEM_SHORT_SWORD] = { .tile = { 's', PALETTE_WHITE}},
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = { .tile = { '}', PALETTE_WHITE}},
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .tile = { 'a', PALETTE_BROWN}},
    /* Shields */
    [ITEM_SHIELD] = { .tile = { 'a', 0}},
    /* Ammo */
    [ITEM_ARROW] = { .tile = { '{', PALETTE_WHITE}},
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
    [ITEM_KEY] = { .tile = { 'k', 0}},
    /* Quest items */
    [ITEM_AMULET] = { .tile = { '"', PALETTE_YELLOW}}
};

static const uint8_t consumable_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = 0,
    /* Melee weapons */
    [ITEM_CLUB] = 0, 
    [ITEM_SHORT_SWORD] = 0,
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = 0,
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = 0,
    /* Shields */
    [ITEM_SHIELD] = 0,
    /* Ammo */
    [ITEM_ARROW] = 0,
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
    [ITEM_KEY] = 0,
    /* Quest items */
    [ITEM_AMULET] = 0
};

static const effect_comp_t effect_base[ITEM_KIND_COUNT] = 
{
    [ITEM_NONE] = { .kind = EFFECT_NONE},
    /* Melee weapons */
    [ITEM_CLUB] = { .kind = EFFECT_NONE},
    [ITEM_SHORT_SWORD] = { .kind = EFFECT_NONE},
    /* Ranged weapons*/
    [ITEM_SHORT_BOW] = { .kind = EFFECT_NONE},
    /* Armour */    
    [ITEM_LEATHER_ARMOUR] = { .kind = EFFECT_NONE},
    /* Shields */
    [ITEM_SHIELD] = { .kind = EFFECT_NONE},
    /* Ammo */
    [ITEM_ARROW] = { .kind = EFFECT_NONE},
    /* Potions */    
    [ITEM_POTION_OF_HEALING] = { .kind = EFFECT_NONE},
    /* Scrolls */
    /* Food and drink */
    [ITEM_BREAD] = { .kind = EFFECT_HEAL, .duration = 0, .triggers = TRIGGER_ON_CONSUMED, .stat = { .magnitude = 5, .attribute = ATTRIBUTE_CUR_HP }},
    /* Rings */
    [ITEM_RING_OF_STRENGTH] = { .kind = EFFECT_STAT_MODIFIER, .duration = 0xFF, .triggers = TRIGGER_ON_EQUIPPED, .stat = { .magnitude = 2, .attribute = ATTRIBUTE_STR }},
    /* Wands */
    /* Light sources */
    /* Keys */
    [ITEM_KEY] = { .kind = EFFECT_NONE},
    /* Quest items */
    [ITEM_AMULET] = { .kind = EFFECT_NONE},
};

static const bool stackable_base[ITEM_KIND_COUNT] =
{
    [ITEM_NONE]              = false,
    /* Melee weapons */
    [ITEM_CLUB]              = false,
    [ITEM_SHORT_SWORD]       = false,
    /* Ranged weapons */
    [ITEM_SHORT_BOW]         = false,
    /* Armour */
    [ITEM_LEATHER_ARMOUR]    = false,
    /* Shields */
    [ITEM_SHIELD]            = false,
    /* Ammo */
    [ITEM_ARROW]             = true,
    [ITEM_BOLT]              = true,
    [ITEM_STONE]             = true,
    [ITEM_DART]              = true,
    /* Potions */
    [ITEM_POTION_OF_HEALING] = true,
    /* Food and drink */
    [ITEM_BREAD]             = true,
    /* Rings */
    [ITEM_RING_OF_STRENGTH]  = false,
    /* Keys */
    [ITEM_KEY]               = false,
    /* Quest items */
    [ITEM_AMULET]            = false,
};

/***************************************************
 * private function prototypes
 ****************************************************/
static void add_pickable(entity_id_t entity);
static void add_stackable(entity_id_t entity, uint8_t quantity);
static void add_equippable(entity_id_t entity, equippable_slot_t slot);
static void melee_add(entity_id_t entity, const attack_comp_t *attack);
static void ranged_add(entity_id_t entity, const attack_comp_t *attack);
static void add_ammo(entity_id_t entity, const ammo_comp_t *ammo);
static void add_effect(entity_id_t entity, const effect_comp_t *effect);
static void add_name(entity_id_t entity, name_id_t name);

/***************************************************
 * public functions
 ***************************************************/

entity_id_t item_system_create(item_kind_t kind, uint8_t quantity)
{
    entity_id_t id = entity_create(); 

    if (id == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;

    /* All items can be picked up */
    add_pickable(id);

    /* Only genuinely stackable items track quantity */
    if (stackable_base[kind])
    {
        add_stackable(id, quantity);
    }
    
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

    /* If item has a ranged attack e.g. bows*/
    if (ranged_base[kind].attack_type == ATTACK_KIND_RANGED)
    {
        ranged_add(id, &ranged_base[kind]);
    }

    /* If item has ammo component e.g. arrow, bolt, trap*/
    if (ammo_base[kind].ammo_type != AMMO_NONE)
    {
        add_ammo(id, &ammo_base[kind]);
    }            

    /* If item has an effect e.g. bread restores health*/
    // text_printf(&g.msg_win, "\nChecking item for effect with kind %d", (uint8_t)effect_base[kind].kind); // TODO remove
    if (effect_base[kind].kind != EFFECT_NONE)
    {
        // text_printf(&g.msg_win, "\nAdding effect with kind %d to item %d", effect_base[kind].kind, id); // TODO remove
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
static void add_pickable(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_PICKABLE));
    entity_set_component(entity, COMPONENT_PICKABLE);
}

static void add_stackable(entity_id_t entity, uint8_t quantity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_STACKABLE)); /* entity must not have item component */
    util_assert(quantity > 0);

    g.stackable_components[entity].quantity = quantity; /* set quantity */

    entity_set_component(entity, COMPONENT_STACKABLE); /* set entity stackable component mask */
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
    g.melee_components[entity].allowed_ammo = attack->allowed_ammo;

    entity_set_component(entity, COMPONENT_MELEE_ATTACK);
}

static void ranged_add(entity_id_t entity, const attack_comp_t *attack)
{
    g.ranged_components[entity].damage_kind = attack->damage_kind;
    g.ranged_components[entity].damage_roll = attack->damage_roll;
    g.ranged_components[entity].damage_mod = attack->damage_mod;
    g.ranged_components[entity].hit_mod = attack->hit_mod;
    g.ranged_components[entity].range = attack->range;
    g.ranged_components[entity].allowed_ammo = attack->allowed_ammo;

    entity_set_component(entity, COMPONENT_RANGED_ATTACK);
}

static void add_ammo(entity_id_t entity, const ammo_comp_t *ammo)
{
    g.ammo_components[entity].ammo_type = ammo->ammo_type;
    g.ammo_components[entity].damage_kind = ammo->damage_kind;
    g.ammo_components[entity].damage_roll = ammo->damage_roll;
    g.ammo_components[entity].damage_mod = ammo->damage_mod;
    g.ammo_components[entity].hit_mod = ammo->hit_mod;
    
    entity_set_component(entity, COMPONENT_AMMO);
}

static void add_effect(entity_id_t entity, const effect_comp_t *effect)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EFFECT)); 

    g.effect_components[entity] = *effect;

    // text_printf(&g.msg_win, "\nAdding effect with kind %d to entity %d", effect->kind, entity); // TODO remove

    entity_set_component(entity, COMPONENT_EFFECT); /* set entity effect component mask */
}

static void add_name(entity_id_t entity, name_id_t name)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_NAME));

    g.name_components[entity] = name; 

    entity_set_component(entity, COMPONENT_NAME);
}
