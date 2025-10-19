/**
 * @file creature_actions.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "creature_actions.h"

#include "global_state.h"
#include "entity.h"

#include "location_comp.h"
#include "contained_comp.h"

#include "text.h"
#include "util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/

bool_t creature_actions_try_pickup(entity_id_t creature, entity_id_t item)
{  
    /* entity to be picked up has item and location components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_LOCATION));

    /* actor has creature, container and location components */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_CONTAINER | COMPONENT_LOCATION));

    /* check creature and item are at the same location*/
    if (!location_equal(creature, item))
    {
        return 0;
    }

    location_remove(item);

    contained_add(item, creature);

    return 1;
}

bool_t creature_actions_try_drop(entity_id_t creature, entity_id_t item)
{
    uint8_t x, y;

    /* entity to be droped has item and contained components */
    util_assert(entity_has_component(item, COMPONENT_ITEM | COMPONENT_CONTAINED));

    /* actor has creature, container and location components */
    util_assert(entity_has_component(creature, COMPONENT_CREATURE | COMPONENT_CONTAINER | COMPONENT_LOCATION));

    /* check creature is holding the item */
    if (!g.contained_components[item].container == creature)
    {
        return 0;
    }

    contained_remove(item);

    x = g.location_components[creature].x;
    y = g.location_components[creature].y;

    text_printf(&g.msg_win, "Dropping %d at (%d,%d)\n", item, x, y);
    location_add(item, x, y);

    return 1;
}