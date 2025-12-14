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
#include "ecs/components/location_comp.h"
#include "ecs/components/item_comp.h"
#include "ecs/components/attack_comp.h"

#include "game/global_state.h"

#include "ecs/systems/systems_dispatch.h"
#include "core/text.h"



/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * public functions
 ***************************************************/

void entity_init(void)
{
    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.entity_components.entities[i].flags = FLAG_NONE; /* clear flags */
        g.entity_components.entities[i].mask = COMPONENT_NONE;  /* clear component mask */
    }

    g.entity_components.active_head = 0;
    g.entity_components.destroy_head = 0;
}

entity_id_t entity_create(void)
{
    if (g.entity_components.active_head == MAX_ENTITIES)
    {
        return ENTITY_ID_INVALID;
    }

    for(uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        if(!entity_has_flag(i, FLAG_IN_USE))
        {
            g.entity_components.entities[i].flags = FLAG_NONE | FLAG_IN_USE;        /* clear flags and set entity in use flag */
            g.entity_components.entities[i].mask = COMPONENT_NONE;                  /* clear component mask */

            g.entity_components.active_list[g.entity_components.active_head++] = i;/* store in active list */

            return i;
        }
    }
    return ENTITY_ID_INVALID;
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
    g.entity_components.destroy_list[g.entity_components.destroy_head++] = id;
    entity_set_flag(id, FLAG_PENDING_DESTROY);
}

/*
 * @brief Destroy all entities marked for destruction
 */
void entity_cleanup() 
{
    for (uint8_t i = 0; i < g.entity_components.destroy_head; i++)
    {
        entity_destroy(g.entity_components.destroy_list[i]);
    }

    /* Set destroy list to empty */
    g.entity_components.destroy_head = 0;
}

/*
 * @brief Finalise entity destruction
 * @details Cleanup routines must have been called before calling this function
 */
void entity_destroy(entity_id_t id)
{
    if (id >= MAX_ENTITIES || !entity_has_flag(id, FLAG_IN_USE))
    {
        return; /* invalid ID or entity not in use */
    }

    text_printf(&g.msg_win, "Destroying entity %d\n",id);

    /* Clear all components associated with this entity */
    if (entity_has_component(id, COMPONENT_CONTAINED)) {
        contained_remove(id);
    }
    if (entity_has_component(id, COMPONENT_CONTAINER)) {
        container_remove(id);
    } 
    if (entity_has_component(id, COMPONENT_CREATURE)) {
        creature_remove(id);
    }
    if (entity_has_component(id, COMPONENT_ITEM)) {
        item_remove(id);
    }
    if (entity_has_component(id, COMPONENT_LOCATION)) {
        location_remove(id);
    }
    if (entity_has_component(id, COMPONENT_PLAYER_CTRL)) { 
        player_remove(id);
    }    
    if (entity_has_component(id, COMPONENT_RENDERABLE)) {
        renderable_remove(id);
    }
    if (entity_has_component(id, COMPONENT_TIMER)) {
        timer_remove(id);
    }
    if (entity_has_component(id, COMPONENT_EQUIPPABLE)) {
        equippable_remove(id);
    }
    if (entity_has_component(id, COMPONENT_MELEE)) {
        melee_remove(id);
    }
    if (entity_has_component(id, COMPONENT_RANGED)) {
        ranged_remove(id);
    }
    if (entity_has_component(id, COMPONENT_SLOTS)) {
        slots_remove(id);
    }
    if (entity_has_component(id, COMPONENT_EQUIPPED)) {
        equipped_remove(id);
    }

    /* mark entity as no longer active and free to use */
    g.entity_components.entities[id].flags = FLAG_NONE;             /* clear all flags including FLAG_IN_USE (in use) */
    g.entity_components.entities[id].mask = COMPONENT_NONE;         /* clear component mask */

    /* remove from active list */
    for (uint8_t i = 0; i < g.entity_components.active_head; i++)
    {
        if (g.entity_components.active_list[i] == id)
        {
            g.entity_components.active_list[i] = g.entity_components.active_list[--g.entity_components.active_head];
            break;
        }
    }    
}

 /***************************************************
 * private functions
 ***************************************************/