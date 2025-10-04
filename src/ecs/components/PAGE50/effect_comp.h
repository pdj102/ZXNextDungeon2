/**
 * @file effect_comp.h
 * @author Paul Johnson
 * @brief Describes an effect that could happen 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef EFFECT_COMP_H
#define EFFECT_COMP_H

#include <stdint.h>

#include "core/util.h"

#include "ecs/entity.h"

#include "game/game.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    EFFECT_NONE = 0,
    EFFECT_RESTORE_HP,
    EFFECT_DAMAGE_HP,
} effect_type_t;

typedef enum {
    TRIGGER_NONE = 0,
    TRIGGER_CONSUMED,       /* eat food, quaff potion*/
    TRIGGER_EQUIPPED,       /* wield / wear */
    TRIGGER_UNEQUIPPED,        
    TRIGGER_HIT,            /* struck by */
    TRIGGER_STEP,           /* stepped on */
    TRIGGER_TURN,           /* turn occurs*/
} effect_trigger_t;

/* A single effect  */
typedef struct {
    effect_type_t type;         /* type of effect */
    int8_t value;               /* value of effect */
    uint8_t duration;           /* duration of effect. 0 = instant effect*/
    uint8_t stat;               /* stat to affect */
    uint8_t status;             /* status to affect */
    effect_trigger_t trigger;   /* condition that determines when an effect is applied */
} effect_comp_t;

typedef effect_comp_t effect_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void effect_init(void);

void effect_add(entity_id_t entity, const effect_comp_t effect);

void effect_remove(entity_id_t entity);

#endif // EFFECT_COMP_H
