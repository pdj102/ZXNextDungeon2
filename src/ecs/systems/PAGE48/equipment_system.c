/**
 * @file equipment_system.c
 * @author Paul Johnson
 * @brief Equippable items can be equipped in slots on the player. Equipped items have an equipped component
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "equipment_system.h"

#include <sys\types.h>

#include "ecs/entity.h"
#include "ecs/components/equippable_comp.h"
#include "ecs/components/equipped_comp.h"
#include "ecs/components/slots_comp.h"

#include "core/util.h"
#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/



/***************************************************
 * public functions
 ***************************************************/
void equipment_system_init(void)
{

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
        /* unequip */ 
    }
    if (entity_has_component(id, COMPONENT_SLOTS))
    {
        /* unequip all items and mark for destruction */
    }    
}