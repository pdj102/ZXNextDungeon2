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

uint8_t item_add(entity_id_t entity, item_kind_t kind, uint8_t quantity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_ITEM)); /* entity must not have item component */
    util_assert(kind < ITEM_KIND_COUNT);
    util_assert(quantity > 0);

    g.item_components[entity].kind = kind; /* set item kind */
    g.item_components[entity].quantity = quantity; /* set quantity */

    entity_set_component(entity, COMPONENT_ITEM); /* set entity item component mask */

    return 1; /* success */
}

zxnext_tile_t *item_get_tile(entity_id_t entity)
{
    return &(item_bases[g.item_components[entity].kind].tile);
}

void item_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_ITEM))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_ITEM); /* clear entity item component mask */
}