/**
 * @file slots_comp.c
 * @author Paul Johnson
 * @brief SLOTSment slot component 
 * 
 */

#include "slots_comp.h"

#include <sys\types.h>      /* bool_t */

#include "ecs/entity.h"

#include "game/global_state.h"
#include "core/util.h"


/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * public functions
 ***************************************************/
/*
 * There can only be one player slot component 
*/
void slots_add(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);

    g.slots[SLOT_HEAD] = ENTITY_ID_INVALID;
    g.slots[SLOT_NECK] = ENTITY_ID_INVALID;
    g.slots[SLOT_BODY] = ENTITY_ID_INVALID;
    g.slots[SLOT_HANDS] = ENTITY_ID_INVALID;
    g.slots[SLOT_SHIELD] = ENTITY_ID_INVALID;    
    g.slots[SLOT_FINGER_LEFT] = ENTITY_ID_INVALID;
    g.slots[SLOT_FINGER_RIGHT] = ENTITY_ID_INVALID;
    g.slots[SLOT_LEGS] = ENTITY_ID_INVALID;
    g.slots[SLOT_FEET] = ENTITY_ID_INVALID;
    g.slots[SLOT_MELEE] = ENTITY_ID_INVALID;
    g.slots[SLOT_RANGED] = ENTITY_ID_INVALID;
    g.slots[SLOT_AMMO] = ENTITY_ID_INVALID;

    entity_set_component(id, COMPONENT_SLOTS); 
}

void slots_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    util_assert( g.slots[SLOT_HEAD] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_NECK] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_BODY] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_HANDS] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_SHIELD] == ENTITY_ID_INVALID);    
    util_assert( g.slots[SLOT_FINGER_LEFT] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_FINGER_RIGHT] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_LEGS] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_FEET] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_MELEE] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_RANGED] == ENTITY_ID_INVALID);
    util_assert( g.slots[SLOT_AMMO] == ENTITY_ID_INVALID);

    entity_clear_component(entity, COMPONENT_SLOTS); 
}