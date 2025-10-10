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

#include "global_state.h"
#include "entity_priv.h"

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

entity_id_t entity_create(entity_type_t type, uint16_t mask)
{
    if (g.entity_arena.free_head >= MAX_ENTITIES)
    {
        return ENTITY_ID_INVALID; /* no free entities */
    }
    entity_id_t id = g.entity_arena.free_ids[g.entity_arena.free_head++]; /* pop from free list */
    g.entity_arena.entities[id].alive = 1;                                /* mark entity as alive */
    g.entity_arena.entities[id].mask = 0;                                 /* clear component mask */
    g.entity_arena.entities[id].type = type;                              /* set entity type */
    g.entity_arena.entities[id].mask = mask;                              /* set component mask */

    return id;
}

entity_id_t *entity_get(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !g.entity_arena.entities[id].alive)
    {
        return NULL; /* invalid ID or entity not alive */
    }
    return &id;
}

void entity_destroy(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !g.entity_arena.entities[id].alive)
    {
        return; /* invalid ID or entity not alive */
    }

    g.entity_arena.entities[id].alive = 0;                    /* mark entity as free */
    g.entity_arena.entities[id].mask = 0;                     /* clear component mask */
    g.entity_arena.free_ids[--g.entity_arena.free_head] = id; /* add back to free list */
}