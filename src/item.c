/**
 * @file item.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "item.h"

#include "global_state.h"
#include "entity.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/
const item_base_t item_bases[ITEM_KIND_COUNT] = {
    [ITEM_NONE]   = { "None",   0, 0, 0, 0 },
    [ITEM_SWORD]  = { "Sword",  10, 2, 5, 20 },
    [ITEM_SHIELD] = { "Shield", 11, 3, 0, 15 },
    [ITEM_POTION] = { "Potion", 12, 1, 0, 5 },
    [ITEM_KEY]    = { "Key",    13, 0, 0, 1 },
};

/***************************************************
 * public functions
 ***************************************************/
entity_id_t item_create(item_type_t type, uint8_t quantity)
{
    entity_id_t id = entity_create( ENTITY_ITEM, COMPONENT_ITEM); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Initialize item component */
    item_component_t *ic = &(g.item_components[id]); /* get item component for this entity */
    ic->type = type;
    ic->quantity = quantity;

    return id;
}

void item_destroy(entity_id_t id)
{
    entity_destroy(id); /* */
}