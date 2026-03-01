/**
 * @file player_comp.h
 * @author Paul Johnson
 * @brief 
 */

#ifndef player_comp_H
#define player_comp_H

#include <stdint.h>

#include "ecs/entity.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    PLAYER_CLASS_FIGHTER = 0,
    PLAYER_CLASS_COUNT
} player_class_t;

typedef struct {
    entity_id_t    id;
    uint8_t        level;
    uint16_t       xp;
    player_class_t class;
} player_comp_t;

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // player_comp_H
