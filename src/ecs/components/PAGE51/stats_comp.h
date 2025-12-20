/**
 * @file stat_comp.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef STATS_COMP_H
#define STATS_COMP_H

#include <stdint.h>

#include "ecs/entity.h"

#include "game/game.h"

#include "core/text.h"
#include "core/util.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Creature stats block */
typedef struct {
    speed_t speed;
    uint8_t stats[STAT_COUNT];
} stats_comp_t;

typedef stats_comp_t stats_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void stats_add(entity_id_t entity, const stats_comp_t stats);

void stats_remove(entity_id_t entity);

#endif // STATS_COMP_H
