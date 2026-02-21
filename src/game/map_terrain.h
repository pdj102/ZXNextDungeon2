/**
 * @file map_terrain.h
 * @author Paul Johnson
 * @brief 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MAP_TERRAIN_H
#define MAP_TERRAIN_H

#include <stdint.h>

#include "core/zxnext.h"

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
typedef enum {
    TERRAIN_FLAGS_NONE          = 0,
    TERRAIN_FLAG_BLOCKS_LOS     = 1 << 0,
    TERRAIN_FLAG_BLOCKS_MOVE    = 1 << 1
} terrain_flags_t;

 typedef enum {
    TERRAIN_NONE = 0,
    TERRAIN_WALL,
    TERRAIN_FLOOR,
    TERRAIN_TYPE_COUNT
} terrain_type_t;

typedef struct {
    const char *name;   
    zxnext_tile_t tile;
    terrain_flags_t flags;
} terrain_base_t;

/***************************************************
 * public variables
 ***************************************************/
extern const terrain_base_t terrain_bases[];

/***************************************************
 * public function prototypes
 ***************************************************/

#endif // MAP_TERRAIN_H
