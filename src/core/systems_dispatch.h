/**
 * @file systems_dispatch.h
 * @author Paul Johnson
 * @brief Game SYSTEMS_DISPATCH
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SYSTEMS_DISPATCH_H
#define SYSTEMS_DISPATCH_H

#include <stdint.h>

#include "../ecs/entity.h"

 /***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public function prototypes
 ***************************************************/

/* Timer System */
void system_timer_init(void);
void system_timer_update(void);

/* Container System*/
void system_container_init(void);
bool_t system_container_place_item_in(entity_id_t container, entity_id_t item);
void system_container_remove_item_from(entity_id_t container, entity_id_t item);
void system_container_mark_contents_for_destruction(entity_id_t container);
void system_container_clean_up(void);

#endif // SYSTEMS_DISPATCH_H