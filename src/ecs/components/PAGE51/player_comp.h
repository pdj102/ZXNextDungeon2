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
typedef struct {
    entity_id_t id;
} player_comp_t;

/***************************************************
 * public function prototypes
 ***************************************************/
void player_add(entity_id_t entity);
void player_remove(entity_id_t entity);

#endif // player_comp_H
