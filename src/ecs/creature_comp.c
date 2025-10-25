/**
 * @file creature_comp.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "creature_comp.h"

#include <arch/zxn.h>

#include "entity.h"
#include "creature_comp_priv.h"
#include "PAGE30/creature_base.h"

#include "../game/global_state.h"
#include "../core/util.h"


/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
void creature_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.creature_components[i].kind = CREATURE_NONE; /* mark all creatures as none */
    }
}

uint8_t creature_add(entity_id_t entity, creature_kind_t kind)
{
    uint8_t current_bank;

    util_assert(entity < MAX_ENTITIES);
    util_assert(kind < CREATURE_KIND_COUNT);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(30); /* Map (bank 30) into ZX Spectrum 8k MMU slot 6 */    
    
    creature_base_init(entity, kind);
    
    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);     

    entity_set_component(entity, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
}

void creature_get_tile(entity_id_t id, zxnext_tile_t *tile)
{
    uint8_t current_bank;

    current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(30); /* Map (bank 30) into ZX Spectrum 8k MMU slot 6 */

    tile->tile_attr = creature_bases[g.creature_components[id].kind].tile.tile_attr;
    tile->tile_id = creature_bases[g.creature_components[id].kind].tile.tile_id;

    /* restore previous bank */
    ZXN_WRITE_MMU6(current_bank);    
}

void creature_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_CREATURE))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_CREATURE); /* clear entity creature component mask */
}