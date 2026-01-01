/**
 * @file equipment_system.c
 * @author Paul Johnson
 * @brief Equippable items can be equipped in player slots. Equipped items have an equipped component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "equipment_system.h"

#include <stdbool.h>

#include "ecs/entity.h"

#include "ecs/components/components.h"

#include "ecs/systems/systems_dispatch.h"

#include "core/util.h"
#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/

/***************************************************
 * private function prototypes
 * ***************************************************/
 static void remove_equippable(entity_id_t entity);
 static uint8_t add_equipped(entity_id_t entity, entity_id_t equipped_by);
 static void remove_equipped(entity_id_t entity);
 static void remove_slots(entity_id_t entity);

/***************************************************
 * public functions
 ***************************************************/
void equipment_system_init(void)
{

}

bool equipment_system_try_equip(entity_id_t actor, entity_id_t item)
{
    event_t event;

    slot_t slot = SLOT_NONE;

    /* actor must have slots component */
    if (!entity_has_component(actor, COMPONENT_SLOTS))
    {
        return 0;
    }
    /* item must have equippable component */
    if (!entity_has_component(item, COMPONENT_EQUIPPABLE))
    {
        return 0;
    }
    /* item must not already be equipped */
    if (entity_has_component(item, COMPONENT_EQUIPPED))
    {
        return 0;
    }

    /* Identify the equip slot to use */
    switch (g.equippable_components[item].slot)
    {
        case EQUIPPABLE_HEAD:
        {
            slot = SLOT_HEAD;
            break;
        }
        case EQUIPPABLE_NECK:
        {
            slot = SLOT_NECK;
            break;
        }        
        case EQUIPPABLE_BODY:
        {
            slot = SLOT_BODY;
            break;
        }        
        case EQUIPPABLE_HANDS:
        {
            slot = SLOT_HANDS;
            break;
        }
        case EQUIPPABLE_FINGER:
        {
            if (g.slots[SLOT_FINGER_LEFT] == ENTITY_ID_INVALID)
            {
                slot = SLOT_FINGER_LEFT;
            } 
            else
            {
                slot = SLOT_FINGER_RIGHT;
            }
            break;
        }
        case EQUIPPABLE_FEET:
        {
            slot = SLOT_FEET;
            break;
        }
        case EQUIPPABLE_LEGS:
        {
            slot = SLOT_LEGS;
            break;
        }
        case EQUIPPABLE_MELEE:
        {
            slot = SLOT_MELEE;
            break;
        }
        case EQUIPPABLE_RANGED:
        {
            slot = SLOT_RANGED;
            break;
        }
        case EQUIPPABLE_AMMO:
        {
            slot = SLOT_AMMO;
            break;
        }
        default:
        {
            return 0;
        }
    }

    /* Equip item*/
    g.slots[slot] = item;
    add_equipped(item, actor);

    event.type = EVENT_EQUIPPED;
    event.source = actor;
    event.target = item;
    event.value = 1;

    system_event_emit(&event);
    
    return 1;
}


bool equipment_system_try_unequip(entity_id_t actor, entity_id_t item)
{
    event_t event;
    
    /* actor must have slots component */
    if (!entity_has_component(actor, COMPONENT_SLOTS))
    {
        return 0;
    }

    equipment_system_is_equipped(actor, item);

    /* Iterate through slots to find item slot and remove */

    for (slot_t slot = 0; slot < SLOT_COUNT; slot++)
    {
        if (g.slots[slot] == item)
        {
            /* Found slot, unequip the item*/
            g.slots[slot] = ENTITY_ID_INVALID;
            g.equipped_components[item].equipped_by = ENTITY_ID_INVALID;
            remove_equipped(item);

            event.type = EVENT_UNEQUIPPED;
            event.source = actor;
            event.target = item;
            event.value = 1;

            system_event_emit(&event);
            return 1;
        }
    }
    return 0;
}

/*
 * @brief Check if an entity is equipped
 */
bool equipment_system_is_equipped(entity_id_t actor, entity_id_t item)
{
    /* item must be equipped */
    if (!entity_has_component(item, COMPONENT_EQUIPPED))
    {
        return 0;
    }

    return g.equipped_components[item].equipped_by == actor;    
}

 /*
 * @brief Clean up an entity marked for destruction.
 * @details 
 * If entity is equipped then unequip it
 * If entity has slots then unequip all items from slots and mark them for destruction
 * 
 * @param id Identity of the entity to be cleaned up. 
 */
void equipment_system_clean_up(entity_id_t id)
{
    if (entity_has_component(id, COMPONENT_EQUIPPED))
    {
        /* TODO unequip item */ 
    }
    if (entity_has_component(id, COMPONENT_SLOTS))
    {
        /* TODO unequip all items and mark for destruction */
    }    
}

 /***************************************************
 * private functions
 ***************************************************/
static void remove_equippable(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    entity_clear_component(entity, COMPONENT_EQUIPPABLE); /* clear entity equippable component mask */
}

static uint8_t add_equipped(entity_id_t entity, entity_id_t equipped_by)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_EQUIPPED)); /* entity must not have equipped component */

    g.equipped_components[entity].equipped_by = equipped_by; 

    entity_set_component(entity, COMPONENT_EQUIPPED); /* set entity equipped component mask */

    return 1; /* success */
}

static void remove_equipped(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(g.equipped_components[entity].equipped_by == ENTITY_ID_INVALID);
    entity_clear_component(entity, COMPONENT_EQUIPPED); /* clear entity equipped component mask */
}

static void remove_slots(entity_id_t entity)
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