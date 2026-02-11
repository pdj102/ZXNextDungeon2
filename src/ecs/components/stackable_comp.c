/**
 * @file stackable_comp.c
 * @author Paul Johnson
 * @brief Stackable component helper functions
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ecs/components/stackable_comp.h"

#include <stdint.h>
#include <stdbool.h>

#include "ecs/entity.h"
#include "game/global_state.h"

/***************************************************
 * public functions
 ***************************************************/

/**
 * @brief Reduce quantity of stackable entity or mark for destruction
 * @details If entity is stackable, decrements quantity and destroys when zero.
 *          If not stackable, marks for destruction immediately.
 */
void stackable_consume_or_destroy(entity_id_t entity)
{
    if (entity_has_component(entity, COMPONENT_STACKABLE))
    {
        g.stackable_components[entity].quantity--;
        if (g.stackable_components[entity].quantity == 0)
        {
            entity_mark_for_destruction(entity);
        }
        return;
    }
    entity_mark_for_destruction(entity);
}
