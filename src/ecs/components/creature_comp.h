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
    CREATURE_CLASS_NONE = 0,
    CREATURE_CLASS_ABERRATIONS,
    CREATURE_CLASS_BEASTS,
    CREATURE_CLASS_CELESTIALS,
    CREATURE_CLASS_CONSTRUCTS,
    CREATURE_CLASS_DRAGONS,
    CREATURE_CLASS_ELEMENTALS,
    CREATURE_CLASS_FEY,
    CREATURE_CLASS_FIENDS,
    CREATURE_CLASS_GIANTS,
    CREATURE_CLASS_HUMANOIDS,
    CREATURE_CLASS_MONSTROSITIES,
    CREATURE_CLASS_OOZES,
    CREATURE_CLASS_PLANTS,
    CREATURE_CLASS_UNDEAD
} creature_class_t;

typedef enum creature_kind_e {
    CREATURE_NONE = 0,
   /* CREATURE_CLASS_ABERRATIONS */
   /* CREATURE_CLASS_BEASTS */    
    CREATURE_RAT,
   /* CREATURE_CLASS_CELESTIALS */
   /* CREATURE_CLASS_CONSTRUCTS */
   /* CREATURE_CLASS_DRAGONS */
   /* CREATURE_CLASS_ELEMENTALS */
   /* CREATURE_CLASS_FEY */
   /* CREATURE_CLASS_FIENDS */
   /* CREATURE_CLASS_GIANTS */
   /* CREATURE_CLASS_HUMANOIDS */    
    CREATURE_COMMONER,
    CREATURE_PLAYER,
    /* CREATURE_CLASS_MONSTROSITIES */
    /* CREATURE_CLASS_OOZES */
    /* CREATURE_CLASS_PLANTS */    
    CREATURE_WITHERWEED, 
    CREATURE_KIND_COUNT
} creature_kind_t;

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
} creature_speed_t;

/* Creature stats block */
typedef struct {
    int8_t ac;
    int8_t cur_hp;
    int8_t max_hp;
    creature_speed_t speed;
    int8_t str;
    int8_t dex;
    int8_t con;
    int8_t inte;
    int8_t wis;
    int8_t cha;
} creature_stats_comp_t;

typedef struct {
    creature_kind_t kind;   /* index into creature_comp_bases[] */
    uint8_t challenge;      /* challenge rating */
} creature_comp_t;

typedef creature_comp_t creature_components_t[MAX_ENTITIES]; 
typedef creature_stats_comp_t creature_stats_components_t[MAX_ENTITIES];

/***************************************************
 * public function prototypes
 ***************************************************/
void creature_init(void);

uint8_t creature_add(entity_id_t entity, creature_kind_t kind, uint8_t challenge);
uint8_t stats_add(entity_id_t entity, creature_stats_comp_t *stats_p);

void creature_speed_to_turns_ticks(entity_id_t id, turn_tick_t *turns_ticks);

void creature_remove(entity_id_t entity);
uint8_t stats_remove(entity_id_t entity);

#endif // CREATURE_COMP_H
