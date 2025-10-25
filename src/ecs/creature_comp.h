/**
 * @file creature_comp.h
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef CREATURE_COMP_H
#define CREATURE_COMP_H

#include <stdint.h>

#include "entity.h"

#include "../core/text.h"
#include "../core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum creature_kind_e {
    CREATURE_NONE = 0,
    CREATURE_RAT,
    CREATURE_COMMONER,
    CREATURE_KIND_COUNT
} creature_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t creature_add(entity_id_t entity, creature_kind_t type);

void creature_get_tile(entity_id_t id, zxnext_tile_t *tile);

void creature_print_name(text_window_t *win, entity_id_t id);

void creature_remove(entity_id_t entity);

#endif // CREATURE_COMP_H
