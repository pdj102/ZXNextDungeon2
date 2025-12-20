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
} effect_kind_t;

typedef enum {
    TRIGGER_NONE            = 0,
    TRIGGER_ON_CONSUMED     = 1 << 0,       /* eat food, quaff potion*/
    TRIGGER_ON_EQUIPPED     = 2 << 0,       /* wield / wear */
    TRIGGER_ON_UNEQUIPPED   = 3 << 0,        
    TRIGGER_ON_HIT          = 4 << 0,            /* struck by */
    TRIGGER_ON_STEP         = 5 << 0,           /* stepped on */
    TRIGGER_ON_TURN         = 6 << 0,           /* turn occurs*/
} trigger_kind_t;

typedef uint8_t trigger_mask_t; /* bitmask of triggers */

/* A single effect  */
typedef struct {
    effect_kind_t kind;         /* kind of effect */
    int8_t value;               /* value of effect */
    uint8_t duration;           /* duration of effect. 0 = instant effect*/
    uint8_t stat;               /* stat to affect */
    uint8_t status;             /* status to affect */
    trigger_mask_t triggers;    /* triggers that trigger this effect */
} effect_comp_t;

typedef effect_comp_t effect_components_t[MAX_ENTITIES]; 

/***************************************************
 * public function prototypes
 ***************************************************/
void effect_init(void);

void effect_add(entity_id_t entity, const effect_comp_t effect);

void effect_remove(entity_id_t entity);

#endif // EFFECT_COMP_H
