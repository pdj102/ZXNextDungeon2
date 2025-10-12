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
const item_comp_base_t item_bases[ITEM_KIND_COUNT] = {
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
        g.item_components[i].kind = ITEM_NONE; /* mark all items as none */
        g.item_components[i].quantity = 0;    /* clear quantity */
    }
}

/**
 * @brief Initialize item component for an existing entity
 * 
 * @param id 
 */
uint8_t item_init_for_entity(entity_id_t id, entity_kind_t kind, uint8_t quantity)
{
    util_assert(id < MAX_ENTITIES);
    util_assert(kind < ITEM_KIND_COUNT);
    util_assert(quantity > 0);

    g.item_components[id].kind = kind; /* set item kind */
    g.item_components[id].quantity = quantity; /* set quantity */

    entity_set_component(id, COMPONENT_ITEM); /* set entity item component mask */

    return 1; /* success */
}

zxnext_tile_t *item_get_tile(entity_id_t id)
{
    return &(item_bases[g.item_components[id].kind].tile);
}

/**
 * @brief Destroy item component for an entity
 * 
 * @param id 
 */
void item_destroy(entity_id_t id)
{
    entity_clear_component(id, COMPONENT_ITEM); /* clear entity item component mask */
}