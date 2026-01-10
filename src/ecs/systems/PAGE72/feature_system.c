/**
 * @file feature_system.c
 * @author Paul Johnson
 * @brief Features are physical objects in game world.
 */

#include "feature_system.h"

#include "ecs/components/components.h"
#include "ecs/components/effect_comp.h"
#include "ecs/components/name_comp.h"

#include "ecs/systems/PAGE42/event_system.h"

#include "game/global_state.h"

/***************************************************
 * private variables
 * ***************************************************/
static const name_id_t feature_name_base[FEATURE_KIND_COUNT] = 
{
    [FEATURE_NONE] = NAME_NONE,
    // Doors
    [FEATURE_OPEN_DOOR] = NAME_OPEN_DOOR,
    // Containers & Storage
    [FEATURE_CHEST] = NAME_CHEST,
    // Alters
    // Mechanisms (levers, switches, )
    // Traps (hidden)
    // Statues
    // Stairs
    [FEATURE_DOWN_STAIRS] = NAME_DOWN_STAIRS,
    [FEATURE_UP_STAIRS] = NAME_UP_STAIRS,
    // Hazards
};

static const renderable_comp_t renderable_base[FEATURE_KIND_COUNT] = {
    [FEATURE_NONE] = { .tile = {' ', 0}},
    // Doors
    [FEATURE_CLOSED_DOOR] = { .tile = {'+', PALETTE_WHITE}},
    [FEATURE_OPEN_DOOR] = { .tile = {'\'', PALETTE_WHITE}},
    // Containers & Storage
    [FEATURE_CHEST] = { .tile = {'~', PALETTE_WHITE}},
    // Alters
    // Mechanisms (levers, switches, )
    // Traps (hidden)
    // Statues
    // Stairs
    [FEATURE_DOWN_STAIRS] = { .tile = {'<', PALETTE_WHITE}},
    [FEATURE_UP_STAIRS] = { .tile = {'>', PALETTE_WHITE}},
    // Hazards
};


/***************************************************
 * private function prototypes
 ****************************************************/
static void add_name(entity_id_t entity, name_id_t name);

/***************************************************
 * public functions
 ***************************************************/

entity_id_t feature_system_create(feature_kind_t kind)
{
    entity_id_t id = entity_create(); 

    if (id == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;
    
    /* Add renderable component  */
    entity_set_component(id, COMPONENT_RENDERABLE);
    g.renderable_components[id].tile = renderable_base[kind].tile;    

    /* All features have a name component*/
    add_name(id, feature_name_base[kind]);

    /* Openable */
    if (kind == FEATURE_OPEN_DOOR)
    {
        entity_set_component(id, COMPONENT_OPENABLE);
        g.openable_components[id].is_open = true;
    }
    if (kind == FEATURE_CLOSED_DOOR)
    {
        entity_set_component(id, COMPONENT_OPENABLE);
        g.openable_components[id].is_open = false;
        entity_set_flag(id, FLAG_BLOCKING);
    }

    /* Transition */
    if (kind == FEATURE_UP_STAIRS)
    {
        entity_set_component(id, COMPONENT_TRANSITION);
        g.transition_components[id].kind = TRANSITION_UP;
        g.transition_components[id].delta_depth = -1;
    }
    if (kind == FEATURE_DOWN_STAIRS)
    {
        entity_set_component(id, COMPONENT_TRANSITION);
        g.transition_components[id].kind = TRANSITION_DOWN;
        g.transition_components[id].delta_depth = +1;
    }

    return id;
}

/***************************************************
 * private functions
 ****************************************************/
static void add_name(entity_id_t entity, name_id_t name)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_NAME));

    g.name_components[entity] = name; 

    entity_set_component(entity, COMPONENT_NAME);
}
