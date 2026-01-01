/**
 * @file target_mode.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TARGET_MODE_H
#define TARGET_MODE_H

#include <stdint.h>
#include "ecs/entity.h"

#include "game/spatial.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

 typedef enum {
    TARGET_FILTER_NONE      = 0, 
    TARGET_FILTER_ENTITY    = 1 << 0, 
    TARGET_FILTER_TILE      = 1 << 1
 } target_filter_t;

 typedef struct {
    target_filter_t filter;
    uint8_t         max_range; 
    bool            require_los;
    coord_t         source;
    coord_t         cursor;
    bool            target_selected;
    coord_t         selected_tile;
    entity_id_t     selected_entity;
 } target_context_t;

/***************************************************
 * public function prototypes
 ***************************************************/
 void target_mode(target_context_t *tcx);

#endif // TARGET_MODE_H
