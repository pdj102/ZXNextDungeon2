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

#include "zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    CREATURE_NONE = 0,
    CREATURE_RAT,
    CREATURE_HUMAN,
    CREATURE_KIND_COUNT
} creature_kind_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t creature_init_for_entity(entity_id_t id, entity_kind_t type);

zxnext_tile_t *creature_get_tile(entity_id_t id);

void creature_destroy(entity_id_t id);

#endif // CREATURE_COMP_H
