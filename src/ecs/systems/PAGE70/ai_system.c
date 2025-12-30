/**
 * @file ai_system.c
 * @author Paul Johnson
 * @brief

 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ai_system.h"

#include <stdint.h>
#include <stdlib.h>
#include <sys\types.h> /* bool_t */

#include "ecs/entity.h"
#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/global_state.h"
#include "game/map.h"

#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 ***************************************************/
static void idle(entity_id_t entity);
static void ai_sleep(entity_id_t entity);
static void wander(entity_id_t entity);
static void alert(entity_id_t entity);
static void chase(entity_id_t entity);
static void attack(entity_id_t entity);
static void flee(entity_id_t entity);
static void dead(entity_id_t entity);

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
        case EVENT_DIED:
            ai->state = AI_STATE_DEAD;
            break;

        case EVENT_SPOTTED_TARGET:
            util_info("AI event saw entity\n");
            if ((ai->state == AI_STATE_IDLE) || (ai->state == AI_STATE_WANDER))
            {
                util_info("AI state change:alert\n");
                ai->state = AI_STATE_ALERT;
                ai->target = event->target;
                ai->alert_timer = 5;
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
            ai->state = AI_STATE_CHASE;
            ai->target = event->source;
            break;
        }
    }
}

void ai_system_process_entity_turn(entity_id_t entity)
{

    switch (g.ai_components[entity].state)
    {
    case AI_STATE_SLEEP:
        ai_sleep(entity);
        break;
    case AI_STATE_IDLE:
        idle(entity);
        break;
    case AI_STATE_WANDER:
        wander(entity);
        break;
    case AI_STATE_ALERT:
        alert(entity);
        break;
    case AI_STATE_CHASE:
        chase(entity);
        break;
    case AI_STATE_ATTACK:
        attack(entity);
        break;
    case AI_STATE_FLEE:
        flee(entity);
        break;
    case AI_STATE_DEAD:
        dead(entity);
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
    util_info("Idle\n");

    bool_t result; 

    result = system_perception_try_check(entity);
    // result = map_has_line_of_sight(g.location_components[g.player.id].x, g.location_components[g.player.id].y, g.location_components[entity].x, g.location_components[entity].y);

    if (result == 1)
    {
        util_info("Creature sees player\n");
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
 * @brief When alert, the monster does not immediately chase
 */
static void alert(entity_id_t entity)
{
    util_info("Alert\n");
    if (g.ai_components[entity].alert_timer > 0)
        g.ai_components[entity].alert_timer--;
    else
        g.ai_components[entity].state = AI_STATE_CHASE;
}
static void chase(entity_id_t entity)
{
    util_info("Chase\n");
    if (rand() % 4)
        system_movement_try_move_random(entity);
}
static void attack(entity_id_t entity)
{
}
static void flee(entity_id_t entity)
{
}
static void dead(entity_id_t entity)
{
    g.creature_components[entity].status = CREATURE_STATUS_DEAD;
    entity_mark_for_destruction(entity);
}