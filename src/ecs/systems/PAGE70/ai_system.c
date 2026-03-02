/**
 * @file ai_system.c
 * @author Paul Johnson
 * @brief AI system for Spectrum Next roguelike
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ai_system.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h> /* bool */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"
#include "ecs/systems/PAGE52/movement_system.h"

#include "game/global_state.h"
#include "game/map.h"

#include "core/util.h"
#include "core/zxnext.h"
#include <arch/zxn.h>       /* ZXN_WRITE_MMU6 */

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void idle(entity_id_t entity);
static void ai_sleep(entity_id_t entity);
static void wander(entity_id_t entity);
static void attack_target(entity_id_t entity);
static void track_target(entity_id_t entity);
static void search_target(entity_id_t entity);
static void flee(entity_id_t entity);
static void dead(entity_id_t entity);

static bool target_valid(entity_id_t target);
static bool try_acquire_visible_target(entity_id_t entity, entity_id_t target);
static void acquire_target(entity_id_t ai_entity, entity_id_t target);
static void update_last_seen(entity_id_t entity, entity_id_t target);
static bool reached_last_seen(entity_id_t entity);
static void give_up_target(entity_id_t entity);
static bool in_attack_range(entity_id_t ai, entity_id_t target);
static bool move_towards_last_seen(entity_id_t entity);
static void begin_search(entity_id_t entity, uint8_t turns);

/***************************************************
 * public functions
 ***************************************************/
void ai_system_init(void)
{
}

void ai_system_handle_event(const event_t *event)
{
    ai_comp_t *ai;

    if (entity_has_component(event->source, COMPONENT_AI))
    {
        // AI is the source - AI did something
        ai = &g.ai_components[event->source];
        switch (event->type)
        {
        case EVENT_SPOTTED_TARGET:
            util_info("AI event saw entity");
            if ((ai->state == AI_STATE_IDLE) || (ai->state == AI_STATE_WANDER) || (ai->state == AI_STATE_TRACK_TARGET) || ai->state == AI_STATE_SEARCH_TARGET)
            {
                acquire_target(event->source, event->target);
            }
            break;
        case EVENT_KILLED:
            // If the AI killed its target, give up target (switch to idle)
            if (ai->target == event->target)
            {
                give_up_target(event->source);
            }
            break;
        }
    }
    else if (entity_has_component(event->target, COMPONENT_AI))
    {
        // AI is the target - something happened to the AI
        ai = &g.ai_components[event->target];
        switch (event->type)
        {
        case EVENT_ATTACKED:
        case EVENT_DAMAGED:
            // AI was attacked, try to acquire attacker as target
            acquire_target(event->target, event->source);     
            break;
        case EVENT_KILLED:
            // AI was killed, switch to idle state
            ai->state = AI_STATE_IDLE;
            // Set creature status to dead
            if (entity_has_component(event->target, COMPONENT_CREATURE))
            {
                g.creature_components[event->target].status = CREATURE_STATUS_DEAD;
            }
             break;
        }
    }
}

void ai_system_process_entity_turn(entity_id_t entity)
{
    util_assert(entity_has_component(entity, COMPONENT_CREATURE));
    util_assert(entity_has_component(entity, COMPONENT_LOCATION));
    util_assert(entity_has_component(entity, COMPONENT_AI));

    if (g.creature_components[entity].status == CREATURE_STATUS_DEAD)
        return;

    switch (g.ai_components[entity].state)
    {
    case AI_STATE_SLEEP:
        ai_sleep(entity);
        break;
    case AI_STATE_IDLE:
        // util_info("Idle");
        idle(entity);
        break;
    case AI_STATE_WANDER:
        wander(entity);
        break;
    case AI_STATE_ATTACK_TARGET:
        util_info("Attack");   
        attack_target(entity);
        break;
    case AI_STATE_TRACK_TARGET:
        util_info("Track");
        track_target(entity);
        break;
    case AI_STATE_SEARCH_TARGET:
        util_info("Search");
        search_target(entity);
        break;
    case AI_STATE_FLEE:
        flee(entity);
        break;
    }
}

/***************************************************
 * private functions
 ***************************************************/

/*
 * When idle, the monster will check for nearby entities and move randomly
 */
static void idle(entity_id_t entity)
{
    bool result; 

    result = system_perception_try_check(entity);

    if (result == 1)
    {
        util_info("Creature sees player");
        return;
    }
    
    if (rand() % 5 == 0)
        system_movement_try_move_random(entity);
}
static void ai_sleep(entity_id_t entity)
{
}
static void wander(entity_id_t entity)
{
    system_perception_try_check(entity);
}

/*
 * @brief When tracking a target, the monster will move towards the target's last known position
 * @details
 * 1) If the target is no longer valid the monster will switch to idle
 * 2) Try and acquire target, if successful switch to attack target
 * 3) If the monster reaches the target's last known position switch to searching for the target
 * 4) Otherwise move towards the target's last known position
 * 5) If stuck (multiple failed moves), transition to search
 */
static void track_target(entity_id_t entity)
{
    ai_comp_t *ai = &g.ai_components[entity];
    entity_id_t target = ai->target;
    bool moved = false;

    /* 1) Target no longer valid -> idle */
    if (!target_valid(target))
    {
        give_up_target(entity);
        return;
    }

    /* 2) Try and acquire target */
    if (try_acquire_visible_target(entity, target))
        return;

    /* 3) Reached last known position -> search target */
    if (reached_last_seen(entity))
    {
        begin_search(entity, 10);
        return;
    }

    /* 4) Move towards last known position */
    moved = move_towards_last_seen(entity);

    if (!moved)
    {
        /* Try a random move as fallback */
        moved = system_movement_try_move_random(entity);
    }

    /* 5) Track failures - if stuck too long, start searching */
    if (moved)
    {
        ai->stuck_counter = 0;
    }
    else
    {
        ai->stuck_counter++;
        if (ai->stuck_counter >= 3)
        {
            begin_search(entity, 10);
        }
    }
}

/*
 * @brief When searching, the monster will search the area around where the target was last seen for a number of turns.
 * @details
 * 1) If the target is no longer valid the monster will switch to idle
 * 2) Try and acquire target, if successful switch to attack target
 * 3) If search timer has reached zero, give up and switch to idle
 * 4) Otherwise, decrement search timer and continue searching 
 */
static void search_target(entity_id_t entity)
{
    ai_comp_t *ai = &g.ai_components[entity];
    entity_id_t target = ai->target;


    /* 1) Target no longer valid -> idle */
    if (!target_valid(target))
    {
        give_up_target(entity);
        return;
    }

    /* 2) Try and acquire target */
    if (try_acquire_visible_target(entity, target))
        return;    

    /* 3) If search timer has reached zero, give up and switch to idle */
    if (ai->search_timer == 0)
    {
        give_up_target(entity);
        return;
    }

    /* 4) Otherwise, decrement search timer and continue searching */
    ai->search_timer--;
    system_movement_try_move_random(entity);
}

/*
 * @brief When attacking, the monster will attack the target if it is in range and move towards it if not.
 * @details
 * 1) If the target is no longer valid the monster will switch to idle
 * 2) Try to (re)acquire visible target
 * 3) If the target is in range, attack
 * 4) Otherwise move towards target
 * 5) If stuck (multiple failed moves), transition to search
 */
static void attack_target(entity_id_t entity)
{
    ai_comp_t *ai = &g.ai_components[entity];
    entity_id_t target = ai->target;
    bool moved = false;

    /* 1) Target no longer valid -> idle */
    if (!target_valid(target))
    {
        give_up_target(entity);
        return;
    }

    /* 2) Try to (re)acquire visible target */
    if (!try_acquire_visible_target(entity, target))
    {
        ai->state = AI_STATE_TRACK_TARGET;
        ai->stuck_counter = 0;
        return;
    }

    /* 3) If the target is in range, attack */
    if (in_attack_range(entity, target))
    {
        system_combat_try_attack(entity, target, ATTACK_KIND_MELEE);
        ai->stuck_counter = 0;
        return;
    }

    /* 4) Otherwise move towards target */
    moved = move_towards_last_seen(entity);

    if (!moved)
    {
        /* Try a random move as fallback */
        moved = system_movement_try_move_random(entity);
    }

    /* 5) Track failures - if stuck too long, start searching */
    if (moved)
    {
        ai->stuck_counter = 0;
    }
    else
    {
        ai->stuck_counter++;
        if (ai->stuck_counter >= 3)
        {
            begin_search(entity, 10);
        }
    }
}

static void flee(entity_id_t entity)
{
}
static void dead(entity_id_t entity)
{
    g.creature_components[entity].status = CREATURE_STATUS_DEAD;
    entity_mark_for_destruction(entity);
}

static bool target_valid(entity_id_t target)
{
    if (target == ENTITY_ID_INVALID)
        return 0;

    if (!entity_has_component(target, COMPONENT_CREATURE))
        return 0;

    if (!entity_has_component(target, COMPONENT_LOCATION))
        return 0;        

    if (g.creature_components[target].status == CREATURE_STATUS_DEAD)
        return 0;
    
    return 1;
}

static bool try_acquire_visible_target(entity_id_t entity, entity_id_t target)
{
    if (!system_perception_can_see_target(entity, target))
        return 0;

    acquire_target(entity, target);
    return 1;
}

static bool in_attack_range(entity_id_t ai, entity_id_t target)
{
    /* TODO support ranged attacks */
    return system_movement_are_adjacent(ai, target);
}

static void acquire_target(entity_id_t ai_entity, entity_id_t target)
{
    ai_comp_t *ai = &g.ai_components[ai_entity];
    ai->state = AI_STATE_ATTACK_TARGET;
    ai->target = target;
    ai->stuck_counter = 0;
    ai->last_seen.x = g.location_components[target].coord.x;
    ai->last_seen.y = g.location_components[target].coord.y;
}

static void give_up_target(entity_id_t entity)
{
    ai_comp_t *ai = &g.ai_components[entity];
    ai->target = ENTITY_ID_INVALID;
    ai->state  = AI_STATE_IDLE;
    ai->stuck_counter = 0;
}

static void update_last_seen(entity_id_t entity, entity_id_t target)
{
    ai_comp_t *ai = &g.ai_components[entity];
    ai->last_seen.x = g.location_components[target].coord.x;
    ai->last_seen.y = g.location_components[target].coord.y;
}

static bool reached_last_seen(entity_id_t entity)
{
    ai_comp_t *ai = &g.ai_components[entity];
    coord_t *m = &g.location_components[entity].coord;

    return ((m->x == ai->last_seen.x) && (m->y == ai->last_seen.y));
}


static bool move_towards_last_seen(entity_id_t entity)
{
    coord_t *l = &g.ai_components[entity].last_seen;
    return system_movement_try_move_towards(entity, l); 
}

static void begin_search(entity_id_t entity, uint8_t turns)
{
    ai_comp_t *ai = &g.ai_components[entity];
    ai->state = AI_STATE_SEARCH_TARGET;
    ai->search_timer = turns;
    ai->stuck_counter = 0;
}

