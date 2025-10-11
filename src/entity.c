/**
 * @file entity.c
 * @author Paul Johnson
 * @brief Entity management for ECS
 
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "entity.h"

#include <stddef.h> /* NULL */
#include <stdint.h> /* uint8_t, uint16_t etc */
#include <sys/types.h> /* bool_t */

#include "global_state.h"
#include "entity_priv.h"

#include "location_comp.h"
#include "item_comp.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * functions
 ***************************************************/

void entity_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.entity_arena.entities[i].alive = 0; /* mark all entities as free */
        g.entity_arena.entities[i].mask = 0;  /* clear all component masks */
        g.entity_arena.free_ids[i] = i;       /* initialize free list */
    }

    g.entity_arena.free_head = 0; /* point to the first free entity */
}

 entity_id_t entity_create_item(item_type_t type, uint8_t quantity)
{
    entity_id_t id = entity_create( ENTITY_ITEM); 
    if (id == ENTITY_ID_INVALID)
        return id;

    /* Initialize item component */
    if (item_init_for_entity(id, type, quantity) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Initialize location component - not placed yet */
    if (location_init_for_entity(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Initialize sprite component - use item tile */
    if(sprite_init_for_entity(id, item_get_tile(id)) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

entity_id_t entity_create(entity_type_t type)
{
    if (g.entity_arena.free_head >= MAX_ENTITIES)
    {
        return ENTITY_ID_INVALID; /* no free entities */
    }
    entity_id_t id = g.entity_arena.free_ids[g.entity_arena.free_head++]; /* pop from free stack */

    g.entity_arena.entities[id].alive = 1;                                /* mark entity as alive */
    g.entity_arena.entities[id].mask = 0;                                 /* clear component mask */
    g.entity_arena.entities[id].type = type;                              /* set entity type */
    g.entity_arena.entities[id].mask = COMPONENT_NONE;                    /* clear component mask */

    return id;
}

bool_t entity_has_component(entity_id_t id, uint32_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return 0; /* invalid ID */
    }

    return (g.entity_arena.entities[id].mask & comp_mask) != 0;
}

void entity_set_component(entity_id_t id, uint32_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_arena.entities[id].mask |= comp_mask;
}

void entity_clear_component(entity_id_t id, uint32_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_arena.entities[id].mask &= ~comp_mask;
}



void entity_destroy(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !g.entity_arena.entities[id].alive)
    {
        return; /* invalid ID or entity not alive */
    }

    /* Clear all components associated with this entity */
    if (entity_has_component(id, COMPONENT_ITEM)) {
        item_destroy(id);
    }
    if (entity_has_component(id, COMPONENT_LOCATION)) {
        location_destroy(id);
    }
    if (entity_has_component(id, COMPONENT_SPRITE)) {
        sprite_destroy(id);
    }

    /* mark entity as free */
    g.entity_arena.entities[id].alive = 0;                    /* mark as not alive*/
    g.entity_arena.entities[id].mask = 0;                     /* clear component mask */
    g.entity_arena.free_ids[--g.entity_arena.free_head] = id; /* add back to free list */
}