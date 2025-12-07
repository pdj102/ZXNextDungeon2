/**
 * @file equipment_system.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "equipment_system.h"

#include "ecs/components/item_comp.h"

#include "game/global_state.h"

#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const equipment_base_t equipment_bases[ITEM_KIND_COUNT] = {
    [ITEM_NONE]             = { .class=ITEM_CLASS_NONE,     .name="None",           {.tile_id=' ',.tile_attr=0},   .weight=0,.value=0,.flags=0},
    [ITEM_CLUB]             = { .class=ITEM_CLASS_MELEE,    .name="Club",           {.tile_id='s', .tile_attr=0},  .weight=2, .value=1, .flags=0 },    
    [ITEM_SHORT_SWORD]      = { .class=ITEM_CLASS_MELEE,    .name="Short sword",    {.tile_id='s', .tile_attr=0},  .weight=2, .value=10, .flags=0 },
    [ITEM_LEATHER_ARMOUR]   = { .class=ITEM_CLASS_ARMOUR,   .name="Leather armour", {.tile_id='s', .tile_attr=0},  .weight=10, .value=10, .flags=0 },
    [ITEM_SHIELD]           = { .class=ITEM_CLASS_SHIELD,   .name="Shield",         {.tile_id='s', .tile_attr=0},  .weight=6, .value=10, .flags=0 },
    [ITEM_POTION_OF_HEALING]= { .class=ITEM_CLASS_POTION,   .name="Potion of healing", {.tile_id='p', .tile_attr=0}, .weight=1, .value=50, .flags=0 },
    [ITEM_KEY]              = { .class=ITEM_CLASS_KEY,      .name="Iron key",       {.tile_id='k', .tile_attr=0},   .weight=1, .value=0, .flags=0 },
};

const renderable_comp_t equipment_renderable_base[ITEM_KIND_COUNT] = {
    [ITEM_NONE] = { .tile = {' ', 0}},
    [ITEM_CLUB] = { .tile = { 's', 0}},
    [ITEM_SHORT_SWORD] = { .tile = { 's', 0}},
    [ITEM_LEATHER_ARMOUR] = { .tile = { 'a', 0}},
    [ITEM_SHIELD] = { .tile = { 'a', 0}},
    [ITEM_POTION_OF_HEALING] = { .tile = { 'p', 0}},
    [ITEM_KEY] = { .tile = { 'k', 0}}
};

/***************************************************
 * public functions
 ***************************************************/

 void equipment_system_init(void)
 {

 }

entity_id_t equipment_system_create(item_kind_t kind, uint8_t quantity)
{
    zxnext_tile_t tile; 

    entity_id_t id = entity_create(); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Add item component */
    if (item_add(id, kind, quantity) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add renderable component  */
    if(renderable_add(id, equipment_renderable_base[kind].tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

void equipment_system_print_name(text_window_t *win, item_kind_t kind)
{
    text_print_string(win, equipment_bases[kind].name);
}

/* TODO change to use kind */
void equipment_system_get_tile(entity_id_t id, zxnext_tile_t *tile)
{
    tile->tile_attr = equipment_bases[g.item_components[id].kind].tile.tile_attr;
    tile->tile_id = equipment_bases[g.item_components[id].kind].tile.tile_id;
}

item_class_t equipment_system_get_class(item_kind_t kind)
{
    return equipment_bases[kind].class;
}