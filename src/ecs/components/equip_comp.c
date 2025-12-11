/**
 * @file equip_comp.c
 * @author Paul Johnson
 * @brief Equipment slot component 
 * 
 */

#include "equip_comp.h"

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
void equip_init(void)
{
    g.equip_slots[EQUIP_HEAD] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_NECK] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_BODY] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_HANDS] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_SHIELD] = ENTITY_ID_INVALID;    
    g.equip_slots[EQUIP_FINGER_LEFT] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_FINGER_RIGHT] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_LEGS] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_FEET] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_MELEE] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_RANGED] = ENTITY_ID_INVALID;
    g.equip_slots[EQUIP_AMMO] = ENTITY_ID_INVALID;
}

/*
 * There can only be one player equipment component 
*/
bool_t equip_add(entity_id_t id)
{
    util_assert(id < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    entity_set_component(id, COMPONENT_EQUIP); 

    return 1; /* success */
}

void equip_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert( g.player.id == ENTITY_ID_INVALID);

    util_assert( g.equip_slots[EQUIP_HEAD] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_NECK] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_BODY] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_HANDS] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_SHIELD] == ENTITY_ID_INVALID);    
    util_assert( g.equip_slots[EQUIP_FINGER_LEFT] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_FINGER_RIGHT] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_LEGS] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_FEET] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_MELEE] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_RANGED] == ENTITY_ID_INVALID);
    util_assert( g.equip_slots[EQUIP_AMMO] == ENTITY_ID_INVALID);

    entity_clear_component(entity, COMPONENT_EQUIP); 
}