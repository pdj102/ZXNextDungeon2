/**
 * @file effect_system.c
 * @author Paul Johnson
 * @brief effect system for ECS
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ecs/systems/PAGE58/stats_system.h"
#include "ecs/systems/PAGE60/effect_system.h"
#include "ecs/systems/PAGE60/effect_system_priv.h"

#include "ecs/components/effect_comp.h"
#include "ecs/components/active_effect_comp.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "game/global_state.h"

/***************************************************
 * private defines
#define INVALID_SLOT 0xFF

 /***************************************************
 * private variables (static)
 ***************************************************/

/* Active effects component array - one per entity. 
 * Each active effect component contains a list of active effects currently affecting that entity.
 * Declared at the top 2KB of MMU slot 6 (0xc000) of the MMU as it is too large to fit in the global state struct in slot 0 (0x0000) and needs to be accessed by the effect system and other systems that need to query active effects.
 * Is  paged in/out of memory with the effect system. 
 * NB this is a bit of a hack 
 * The effect system code MUST NOT exceed 6KB in size to ensure there is enough room for the active effects component array in the 8KB MMU slot.
 */
__at (0xd800) active_effect_components_t active_effect_components_priv; 

/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * public functions
 ***************************************************/
void effect_system_init(void)
{
    text_printf(&g.msg_win, "\nActive effects size:%U", sizeof(active_effect_components_priv));
    util_assert(sizeof(active_effect_components_priv) < 0x1FFF); /* Must fit within 8k MMU slot */

    g.active_effect_components = &active_effect_components_priv;

    for (uint8_t i = 0; i < MAX_ENTITIES; i++)
    {
        g.active_effect_components[i]->head = 0;
        for (uint8_t j = 0; j < MAX_ACTIVE_EFFECTS; j++)
        {
            g.active_effect_components[i]->slots[j].effect.kind = EFFECT_NONE;
        }
    }
}



void effect_system_handle_event(const event_t *event)
{
    handle_event(event);
}

void effect_system_process_entity_turn(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(entity_has_component(entity, COMPONENT_ACTIVE_EFFECT));

    entity_turn(entity);
}

int8_t effect_system_attribute_mod_sum(entity_id_t actor, attribute_t attribute)
{
    util_assert(actor < MAX_ENTITIES);
    util_assert(entity_has_component(actor, COMPONENT_ACTIVE_EFFECT));

    return attribute_mod_sum(actor, attribute);
}

void effect_system_cleanup_entity(entity_id_t source)
{
    cleanup_entity(source);
}

 /***************************************************
 * private functions
 ***************************************************/