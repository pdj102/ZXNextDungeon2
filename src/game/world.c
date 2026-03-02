/**
 * @file world.c
 * @author Paul Johnson
 * @brief Game world

 *
 * @copyright Copyright (c) 2025
 *
 */

#include "game/world.h"

#include <stdbool.h>  /* bool */
#include <stdlib.h>   /* abs() */
#include <arch/zxn.h> /* ZXN_WRITE_MMU6 */

#include "ecs/entity.h"
#include "ecs/components/components.h"
#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE40/container_system.h"

#include "game/global_state.h"
#include "game/camera.h"

#include "core/util.h"

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void world_handle_transition(const event_t *event);
static bool world_player_has_quest_item(entity_id_t player);
static void world_check_win_condition(entity_id_t player);

/***************************************************
 * public functions
 ***************************************************/
void new_game(void)
{
    event_t event;

    entity_init();
    component_init();
    systems_init();

    g.player.id = ENTITY_ID_INVALID;
    g.quest_item_spawned = 0;
    entity_id_t e = system_monster_create_player();
    util_assert(e != ENTITY_ID_INVALID);

    map_init();
    camera_init();

     /* Emit initial teleport event to place player in the world and trigger map generation */    
    event.source = ENTITY_ID_INVALID;
    event.target = g.player.id;
    event.type = EVENT_TRANSITION_TELEPORT;
    event.value = 0;

    system_event_emit(&event);
    system_event_process_queue();   /* process the initial transition synchronously */
}

void world_handle_event(const event_t *event)
{
    switch (event->type)
    {
        case EVENT_TRANSITION_TELEPORT:
        case EVENT_TRANSITION:
            world_handle_transition(event);
            break;
        default:
            return;
    }
}

/***************************************************
 * private functions
 ***************************************************/
static void world_handle_transition(const event_t *event)
{
    dungeon_transition_t c;

    c.from_depth = g.depth;                 // transition from current world depth
    c.to_depth = g.depth + event->value;    // to current world depth + delta
    c.actor = event->target;                // e.g. player
    c.source_entity = event->source;        // stairs etc

    // If transition was via a source entity with transition component get the entry kind (e.g. up stairs, down stairs) otherwise default to 0 for teleport/new game
    if (c.source_entity != ENTITY_ID_INVALID && entity_has_component(c.source_entity, COMPONENT_TRANSITION))
    {
        c.entry_kind = g.transition_components[c.source_entity].kind;
    }
    else
    {
        c.entry_kind = 0;  // Default entry kind for teleport/new game
    }

    /* Win condition: player ascends from the shallowest dungeon level with the quest item */
    if (c.from_depth == 1 && c.entry_kind == TRANSITION_UP)
    {
        world_check_win_condition(c.actor);
        if (g.creature_components[c.actor].status == CREATURE_STATUS_WON)
            return;  /* Do not update depth or generate a surface level */
    }

    g.depth = c.to_depth;
    map_gen(&c);
    g.map_win.dirty = 1;
}

void world_destroy_non_persistent_entities(void)
{
    /* Phase 1: mark entities */
    for (uint8_t i = 0; i < g.entity_components.active_head; i++)
    {
        entity_id_t id = g.entity_components.active_list[i];

        if (id == ENTITY_ID_INVALID)
            continue;

        if (!entity_has_flag(id, FLAG_IN_USE))
            continue;

        if (entity_has_flag(id, FLAG_PENDING_DESTROY))
            continue;

        /* Persistent or protected by a persistent container? */
        if (system_container_is_protected_by_persistence(id))
            continue;

        entity_mark_for_destruction(id);
    }

    /* Phase 2: cleanup and destroy entities marked for destruction */
    world_process_entity_destructions();
}

/*
 * @brief Detach persistent entities from the current world state but do NOT destroy them.
 */
void world_detach_persistent_entities(void)
{
    for (entity_id_t id = 0; id < MAX_ENTITIES; ++id)
    {
        if (!entity_has_flag(id, FLAG_IN_USE))
            continue;

        if (!entity_has_flag(id, FLAG_PERSISTANT))
            continue;

        /* Items inside a persistent container (e.g. player inventory) stay put */
        /* TODO is this correct? What if the container is a chest */
        if (entity_has_component(id, COMPONENT_CONTAINED))
            continue;

        world_detach_entity(id);
    }
}

/*
 * @brief Detach entity from the world but do not destroy it
 */
void world_detach_entity(entity_id_t id)
{
    if (!entity_has_flag(id, FLAG_IN_USE))
        return;

    /* Remove from map */
    system_movement_detach(id);

    /* Remove from any container */
    if (entity_has_component(id, COMPONENT_CONTAINED))
    {
        container_system_remove(id);
    }

    /* TODO if the entity is the source of an effect - remove effect */
    // system_effect_cleanup_entity(id);

    /* Stop timer */
    system_timer_stop(id);
}

/*
 * @brief Attach entity to the world
 */
void world_attach_entity(entity_id_t id, uint8_t x, uint8_t y)
{
    if (!entity_has_flag(id, FLAG_IN_USE))
        return;

    /* PLave on map */
    system_movement_place(id, x, y);

    /* Start timer */
    system_timer_start(id);
}

/*
 * @brief Process and finalise all pending entity destructions.
 *
 * This function performs a two-phase destruction:
 *  1) Run system-level cleanup for all entities marked for destruction.
 *     Cleanup may enqueue additional entities.
 *  2) Finalise destruction once the queue stabilizes
 */
void world_process_entity_destructions(void)
{
    uint8_t i = 0;
    entity_id_t id;

    /* Phase 1 - Run clean up for each entity marked for destruction */
    /* Note: clean up may append more entities to the list for destruction */
    /* So we need to iterate until the list is empty */
    /* Do not destroy anything yet */

    while (g.entity_components.destroy_head > i)
    {
        id = g.entity_components.destroy_list[i];
        // text_printf(&g.msg_win, "\n%d entities to cleanup", g.entity_components.destroy_head);

        util_assert(entity_has_flag(id, FLAG_PENDING_DESTROY));
        util_assert(entity_has_flag(id, FLAG_IN_USE));
        system_container_clean_up(id);
        system_effect_cleanup_entity(id);
        system_movement_detach(id);
        system_timer_cleanup(id);
        system_equipment_cleanup(id);

        i++;
    }

    /* Phase 2 - Finalise the destruction of each entity */
    entity_cleanup();
}

static bool world_player_has_quest_item(entity_id_t player)
{
    entity_id_t item = container_system_get_first(player);
    while (item != ENTITY_ID_INVALID)
    {
        if (entity_has_flag(item, FLAG_QUEST_ITEM))
            return true;
        item = container_system_get_next(item);
    }
    return false;
}

static void world_check_win_condition(entity_id_t player)
{
    if (!world_player_has_quest_item(player))
        return;
    g.creature_components[player].status = CREATURE_STATUS_WON;
    text_printf(&g.msg_win, "\nYou escaped with the Amulet of Yendor. You win!");
    g.msg_win.dirty = 1;
}
