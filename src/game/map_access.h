/**
 * @file map_access.h
 * @author Paul Johnson
 * @brief Inline map accessor functions for zero-overhead encapsulation
 *
 * IMPORTANT: This file must be included AFTER global_state.h
 *
 * @copyright Copyright (c) 2025
 */

#ifndef MAP_ACCESS_H
#define MAP_ACCESS_H

#include "game/map.h"
#include "game/global_state.h"

/***************************************************
 * Inline accessor functions - zero overhead encapsulation
 ***************************************************/

/*
 * @brief Get terrain type at map position
 * @param x X coordinate
 * @param y Y coordinate
 * @return terrain type
 */
static inline terrain_type_t map_get_terrain(uint8_t x, uint8_t y)
{
    return g.map.terrain[x][y];
}

/*
 * @brief Set terrain type at map position
 * @param x X coordinate
 * @param y Y coordinate
 * @param terrain Terrain type to set
 */
static inline void map_set_terrain(uint8_t x, uint8_t y, terrain_type_t terrain)
{
    g.map.terrain[x][y] = terrain;
}

/*
 * @brief Set entity head at map position (internal use - for linked list management)
 * @param x X coordinate
 * @param y Y coordinate
 * @param entity Entity ID to set as head of location
 */
static inline void map_set_entity_head(uint8_t x, uint8_t y, entity_id_t entity)
{
    g.map.entity_head[x][y] = entity;
}

#endif // MAP_ACCESS_H
