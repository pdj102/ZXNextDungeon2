/**
 * @file item.c
 * @author Paul Johnson
 * @brief 
 * @date 2025-10-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "item.h"

#include "global_state.h"
#include "entity.h"
#include "util.h"

/***************************************************
 * private defines
 ***************************************************/


/***************************************************
 * private types
 * ***************************************************/


typedef struct {
    const char *name;   // optional (ROM string table)
    uint8_t sprite_id;
    uint8_t weight;
    uint8_t value;
    uint8_t flags;
} item_base_t;




 /***************************************************
 * private function prototypes
 ***************************************************/

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
    entity_id_t id = entity_create(); // assume your entity allocator exists
    if (id == ENTITY_ID_INVALID)
        return id;

   entity_t *e = entity_get(id);

    /* Initialize entity as item */
    e->type = ENTITY_ITEM;
    e->mask |= COMPONENT_ITEM;

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