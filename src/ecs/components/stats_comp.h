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
    int8_t ac;
    int8_t cur_hp;
    int8_t max_hp;
    speed_t speed;
    int8_t str;
    int8_t dex;
    int8_t con;
    int8_t inte;
    int8_t wis;
    int8_t cha;
} stats_comp_t;


typedef stats_comp_t stats_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t stats_add(entity_id_t entity, stats_comp_t *stats_p);

void stats_remove(entity_id_t entity);

#endif // STATS_COMP_H
