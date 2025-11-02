/**
 * @file item_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "item_comp.h"

#include <arch/zxn.h>

#include "entity.h"
#include "item_comp_priv.h"
#include "PAGE32/item_base.h"

#include "../game/global_state.h"
#include "../core/util.h"
#include "../core/zxnext.h"


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

void item_get_tile(entity_id_t id, zxnext_tile_t *tile)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ITEM_BASE);     /* Map item base code into ZX Spectrum 8k MMU slot 6 */    

    tile->tile_attr = item_bases[g.item_components[id].kind].tile.tile_attr;
    tile->tile_id = item_bases[g.item_components[id].kind].tile.tile_id;

    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);   
}

void item_print_name(text_window_t *win, entity_id_t item)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_ITEM_BASE);     /* Map item base code into ZX Spectrum 8k MMU slot 6 */   

    item_base_print_name(win, item);

    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);   
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

 /***************************************************
 * private functions
 ***************************************************/