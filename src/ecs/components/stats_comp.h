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
typedef enum {
    STAT_STR,
    STAT_DEX,
    STAT_CON,
    STAT_INT,
    STAT_WIS,
    STAT_CHA,
    STAT_COUNT,
    STAT_NONE,    
} stat_kind_t;

typedef enum creature_speed_e {
    SPEED_NONE = 0,
    SPEED_5FT, 
    SPEED_10FT,
    SPEED_15FT,
    SPEED_20FT,
    SPEED_25FT,
    SPEED_30FT,
    SPEED_35FT,
    SPEED_40FT,
    SPEED_45FT,
    SPEED_50FT,
    SPEED_55FT,
    SPEED_60FT,
    SPEED_COUNT
} speed_t;

 /* Creature stats block */
typedef struct {
    speed_t speed;
    uint8_t stats[STAT_COUNT];
} stats_comp_t;

typedef stats_comp_t stats_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // STATS_COMP_H
