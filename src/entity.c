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
        g.entity_components.entities[i].flags = FLAG_NONE; /* clear flags */
        g.entity_components.entities[i].mask = COMPONENT_NONE;  /* clear component mask */
        g.entity_components.free_ids[i] = i;       /* initialize free list */
    }

    g.entity_components.free_head = 0; /* point to the first free entity */
}

entity_id_t entity_create(void)
{
    if (g.entity_components.free_head >= MAX_ENTITIES)
    {
        return ENTITY_ID_INVALID; /* no free entities */
    }

    entity_id_t id = g.entity_components.free_ids[g.entity_components.free_head++]; /* pop next free entity from free stack */

    g.entity_components.entities[id].flags = FLAG_INUSE;                    /* mark entity as in use */
    g.entity_components.entities[id].mask = COMPONENT_NONE;                 /* clear component mask */

    return id;
}

bool_t entity_has_component(entity_id_t id, uint16_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return 0; /* invalid ID */
    }

    return (g.entity_components.entities[id].mask & comp_mask) != 0;
}

void entity_set_component(entity_id_t id, uint16_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].mask |= comp_mask;
}

void entity_clear_component(entity_id_t id, uint16_t comp_mask)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].mask &= ~comp_mask;
}

bool_t entity_has_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return 0; /* invalid ID */
    }

    return (g.entity_components.entities[id].mask & flag) != 0;
}

void entity_set_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].mask |= flag;
}

void entity_clear_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].mask &= ~flag;
}


/* 
 * NB  items must have been from container first or will abort. 
 * TODO
 * - destroy contained items
*/
void entity_destroy(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !entity_has_flag(id, FLAG_INUSE))
    {
        return; /* invalid ID or entity not in use */
    }

    /* Clear all components associated with this entity */
    if (entity_has_component(id, COMPONENT_ITEM)) {
        item_remove(id);
    }
    if (entity_has_component(id, COMPONENT_LOCATION)) {
        location_remove(id);
    }
    if (entity_has_component(id, COMPONENT_SPRITE)) {
        sprite_remove(id);
    }
    if (entity_has_component(id, COMPONENT_CONTAINED)) {
        contained_remove(id);
    }
    if (entity_has_component(id, COMPONENT_CONTAINER)) {
        container_remove(id);
    }          
    if (entity_has_component(id, COMPONENT_PLAYER_CTRL)) { 
        player_ctrl_remove(id);
    }

    /* mark entity as free to use */
    g.entity_components.entities[id].flags = FLAG_NONE;             /* clear all flags including inuse */
    g.entity_components.entities[id].mask = COMPONENT_NONE;         /* clear component mask */
    g.entity_components.free_ids[--g.entity_components.free_head] = id; /* add back to free list */
}