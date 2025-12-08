/**
 * @file item_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/components/item_comp.h"

#include <arch/zxn.h>

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


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

void item_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_ITEM); /* clear entity item component mask */
}

uint8_t equip_add(entity_id_t entity, equip_slot_t slot)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EQUIP)); 

    g.equip_components[entity].slot = slot; /* the slot that can be equipped */

    entity_set_component(entity, COMPONENT_EQUIP); 

    return 1; /* success */
}

void equip_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert( g.equip_components[entity].equipped_by == ENTITY_ID_INVALID); /* Item must not be equipped */

    entity_clear_component(entity, COMPONENT_EQUIP); 
}

 /***************************************************
 * private functions
 ***************************************************/