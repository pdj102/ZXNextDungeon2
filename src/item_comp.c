/**
 * @file item_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "item_comp.h"

#include "global_state.h"
#include "entity.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/
const item_comp_base_t item_bases[ITEM_TYPE_COUNT] = {
    [ITEM_NONE]   = { "None",   {' ', 0}, 0, 0, 0, 0 },
    [ITEM_SWORD]  = { "Sword",  {'s', 0}, 10, 2, 5, 20 },
    [ITEM_SHIELD] = { "Shield", {'s', 0}, 11, 3, 0, 15 },
    [ITEM_POTION] = { "Potion", {'p', 0}, 12, 1, 0, 5 },
    [ITEM_KEY]    = { "Key",    {'k', 0}, 13, 0, 0, 1 },
};

/***************************************************
 * public functions
 ***************************************************/
void item_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.item_components[i].type = ITEM_NONE; /* mark all items as none */
        g.item_components[i].quantity = 0;    /* clear quantity */
    }
}

/**
 * @brief Factory function to create an item entity with item, location and sprite components
 * 
 * @param type 
 * @param quantity 
 * @return entity_id_t 
 */
 entity_id_t item_create(item_comp_type_t type, uint8_t quantity)
{
    entity_id_t id = entity_create( ENTITY_ITEM, COMPONENT_ITEM | COMPONENT_LOCATION | COMPONENT_SPRITE); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Initialize item component */
    item_comp_t *ic = &(g.item_components[id]); /* get item component for this entity */
    ic->type = type;
    ic->quantity = quantity;

    /* Initialize location component - not placed yet */
    g.location_components[id].type = LOC_NONE;
    g.location_components[id].next_in_location = ENTITY_ID_INVALID;
    /* Initialize sprite component - use item tile */
    // g.sprite_components[id].tile = item_bases[type].tile;

    return id;
}

/**
 * @brief Initialize item component for an existing entity
 * 
 * @param id 
 */
bool_t item_init_for_entity(entity_id_t entity, item_comp_type_t type, uint8_t quantity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(type < ITEM_TYPE_COUNT);
    util_assert(quantity > 0);

    g.item_components[entity].type = type; /* set item type */
    g.item_components[entity].quantity = quantity; /* set quantity */

    /* TODO set entity item component mask */

    return 1; /* success */
}

/**
 * @brief Destroy item component for an entity
 * 
 * @param id 
 */
void item_destroy(entity_id_t id)
{
    /* TODO unset entity item component mask */
}