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

#include "creature_comp_priv.h"
#include "PAGE30/creature_base.h"

#include "global_state.h"
#include "entity.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/
/*
 const creature_comp_base_t creature_bases[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE]   = { "None",   {' ', 0}, CREATURE_CLASS_NONE, 0, 0, 0 },
    [CREATURE_RAT]    = { "Rat",   {'R', 0}, CREATURE_CLASS_BEASTS, 12, 7, 10},
    [CREATURE_HUMAN]  = { "Human", {'H', 0}, CREATURE_CLASS_HUMANOIDS, 10, 4, 10}
};
*/


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
    util_assert(entity < MAX_ENTITIES);
    util_assert(kind < CREATURE_KIND_COUNT);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    g.creature_components[entity].kind = kind; /* set creature type */
    // todo set up creature 

    entity_set_component(entity, COMPONENT_CREATURE); /* set entity creature component mask */

    return 1; /* success */
}

void creature_get_tile(entity_id_t id, zxnext_tile_t *tile)
{
    uint8_t current_bank;

    /* Remember current bank*/
    current_bank = ZXN_READ_MMU6();

    /* Map (bank 28) into ZX Spectrum 8k MMU slot 6 */
    /* Call banked code */ 
    ZXN_WRITE_MMU6(30);

    tile->tile_attr = creature_bases[g.creature_components[id].kind].tile.tile_attr;
    tile->tile_id = creature_bases[g.creature_components[id].kind].tile.tile_id;

    if ((uint16_t)&test >= 0xa000)
    {
        text_print_string(&g.msg_win, "Above\n");
    }
    if ((uint16_t)&test < 0xc001)
    {
        text_print_string(&g.msg_win, "Below\n");
    }
    text_printf(&g.msg_win, "Memory test():%U\n", (uint16_t)&test);
    text_printf(&g.msg_win, "Memory g:%U\n", (uint16_t)&g);
    text_printf(&g.msg_win, "Memory base:%U\n", (uint16_t)&creature_bases);
    text_printf(&g.msg_win, "Memory tile:%U\n", (uint16_t)&creature_bases[g.creature_components[id].kind].tile.tile_id);
    text_printf(&g.msg_win, "tile %c\n", creature_bases[g.creature_components[id].kind].tile.tile_id);

    test();


    // tile->tile_attr = 0;
    // tile->tile_id = 'T';

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