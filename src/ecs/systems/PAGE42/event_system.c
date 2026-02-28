/**
 * @file event_system.c
 * @author Paul Johnson
 * @brief

 *
 * @copyright Copyright (c) 2025
 *
 */

#include "event_system.h"

#include "ecs/entity.h"

#include "ecs/systems/systems_dispatch.h"

#include "game/world.h"

#include "game/ui.h"

#include "core/util.h"

/***************************************************
 * private defines
 ***************************************************/

#define EVENT_QUEUE_SIZE  8u                        /* Must be a power of 2 */
#define EVENT_QUEUE_MASK  (EVENT_QUEUE_SIZE - 1u)

/***************************************************
 * private variables
 * ***************************************************/

static event_t  s_queue[EVENT_QUEUE_SIZE];
static uint8_t  s_head;   /* Index of next event to dequeue */
static uint8_t  s_tail;   /* Index of next free slot        */
static uint8_t  s_count;  /* Number of events currently queued */

/***************************************************
 * public functions
 ***************************************************/
void event_system_init(void)
{
    s_head  = 0;
    s_tail  = 0;
    s_count = 0;
}

void event_system_emit(const event_t *event)
{
    if (s_count >= EVENT_QUEUE_SIZE)
    {
        util_info("EVT QUEUE FULL");
        return;
    }
    s_queue[s_tail] = *event;
    s_tail = (s_tail + 1u) & EVENT_QUEUE_MASK;
    s_count++;
}

void event_system_process_queue(void)
{
    event_t event;

    while (s_count > 0)
    {
        event  = s_queue[s_head];
        s_head = (s_head + 1u) & EVENT_QUEUE_MASK;
        s_count--;

        system_effect_handle_event(&event);
        system_player_handle_event(&event);
        system_ai_handle_event(&event);
        world_handle_event(&event);
        ui_on_event(&event);
    }
}
