/**
 * @file entity.c
 * @author Paul Johnson
 * @brief Entity management for ECS
 
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ecs/entity.h"

#include <stddef.h> /* NULL */
#include <stdint.h> /* uint8_t, uint16_t etc */
#include <sys/types.h> /* bool_t */

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "game/global_state.h"

#include "ecs/systems/systems_dispatch.h"
#include "core/text.h"

/***************************************************
 * private defines
 ***************************************************/
#define COMP_BYTE(c)   ((c) >> 3)     /* /8 */
#define COMP_BIT(c)    (1u << ((c) & 7))

/***************************************************
 * private variables
 ****************************************************/

/***************************************************
 * private function prototypes
 ****************************************************/
 static void clear_component_mask(entity_id_t id);
 static void active_list_append(entity_id_t id);
 static void active_list_remove(entity_id_t id);
 static void destroy_list_append(entity_id_t id);
static void entity_destroy(entity_id_t id);

/***************************************************
 * public functions
 ***************************************************/

void entity_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.entity_components.entities[i].flags = FLAG_NONE; /* clear flags */
        clear_component_mask(i);
    }

    /* Set active and destory heads to index 0 */
    g.entity_components.active_head = 0;
    g.entity_components.destroy_head = 0;
}

entity_id_t entity_create(void)
{
    if (g.entity_components.active_head == MAX_ENTITIES)
    {
        return ENTITY_ID_INVALID;
    }

    for(uint8_t id = 0; id < MAX_ENTITIES; id++)
    {
        if(!entity_has_flag(id, FLAG_IN_USE))
        {
            g.entity_components.entities[id].flags = FLAG_NONE | FLAG_IN_USE;        /* clear flags and set entity in use flag */
            clear_component_mask(id);

            active_list_append(id); 

            return id;
        }
    }
    return ENTITY_ID_INVALID;
}

bool_t entity_has_component(entity_id_t id, component_id_t comp)
{
    if (id >= MAX_ENTITIES || id == ENTITY_ID_INVALID)
        return 0;

    return (g.entity_components.entities[id]
                .components.mask[COMP_BYTE(comp)] & COMP_BIT(comp)) != 0;
}


void entity_set_component(entity_id_t id, component_id_t comp)
{
    if (id >= MAX_ENTITIES || id == ENTITY_ID_INVALID)
        return;

    g.entity_components.entities[id]
        .components.mask[COMP_BYTE(comp)] |= COMP_BIT(comp);
}


void entity_clear_component(entity_id_t id, component_id_t comp)
{
    if (id >= MAX_ENTITIES || id == ENTITY_ID_INVALID)
        return;

    g.entity_components.entities[id]
        .components.mask[COMP_BYTE(comp)] &= (uint8_t)~COMP_BIT(comp);
}


bool_t entity_has_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return 0; /* invalid ID */
    }

    return (g.entity_components.entities[id].flags & flag) != 0;
}

void entity_set_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].flags |= flag;
}

void entity_clear_flag(entity_id_t id, uint8_t flag)
{
    if (id >= MAX_ENTITIES)
    {
        return; /* invalid ID */
    }

    g.entity_components.entities[id].flags &= ~flag;
}

/*
 * @brief Mark an entity for destruction and append to for destuction list
 */
void entity_mark_for_destruction(entity_id_t id) 
{
    /* append to destruction list */
    destroy_list_append(id);
    entity_set_flag(id, FLAG_PENDING_DESTROY);
}

/*
 * @brief Destroy all entities marked for destruction
 */
void entity_cleanup(void) 
{
    for (uint8_t i = 0; i < g.entity_components.destroy_head; i++)
    {
        entity_destroy(g.entity_components.destroy_list[i]);
    }

    /* Set destroy list to empty */
    g.entity_components.destroy_head = 0;
}



 /***************************************************
 * private functions
 ***************************************************/

 /*
  * @brief clears the component mask of an entity
  */
static void clear_component_mask(entity_id_t id)
{
    for (uint8_t i = 0; i < COMPONENT_BYTES; i++)
    {
        g.entity_components.entities[id].components.mask[i] = 0;
    }
}

/*
 * @brief appends an entity to the active list
 */
static void active_list_append(entity_id_t id)
{
    util_assert ( g.entity_components.active_head < MAX_ENTITIES);
    g.entity_components.active_list[g.entity_components.active_head++] = id; /* store in active list */
}

/*
 * @brief removes an entity from the active list
 */
static void active_list_remove(entity_id_t id)
{
    for (uint8_t i = 0; i < g.entity_components.active_head; i++)
    {
        if (g.entity_components.active_list[i] == id)
        {
            g.entity_components.active_list[i] = g.entity_components.active_list[--g.entity_components.active_head];
            break;
        }
    }   
}

/*
 * @brief appends an entity to the pending destruction list
 */
static void destroy_list_append(entity_id_t id)
{
    util_assert ( g.entity_components.destroy_head < MAX_ENTITIES);
    g.entity_components.destroy_list[g.entity_components.destroy_head++] = id;
}

/*
 * @brief Finalise entity destruction
 * @details Cleanup routines must have been called before calling this function
 */
static void entity_destroy(entity_id_t id)
{
    util_assert(id<MAX_ENTITIES);
    util_assert(entity_has_flag(id, FLAG_IN_USE));

    /* mark entity as no longer active and free to use */
    g.entity_components.entities[id].flags = FLAG_NONE;             /* clear all flags including FLAG_IN_USE (in use) */
    clear_component_mask(id);

    /* remove from active list */
    active_list_remove(id);
}