/**
 * @file dungeon_gen.c
 * @author Paul Johnson
 * @brief
 *
 */

#include "dungeon_gen.h"

#include <stdlib.h>

#include "ecs/systems/systems_dispatch.h"

#include "game/world.h"
#include "game/map.h"
#include "game/map_terrain.h"

#include "game/PAGE34/dungeon_layout.h"

#include "game/global_state.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

/* Spawn table entry */
typedef struct {
    uint8_t kind;        /* item_kind_t or creature_kind_t */
    uint8_t weight;      /* 0-100, higher = more common */
    uint8_t min_qty;     /* minimum quantity (items only) */
    uint8_t max_qty;     /* maximum quantity (items only) */
} spawn_entry_t;

/* Depth tier spawn table */
typedef struct {
    const spawn_entry_t *creature_table;
    uint8_t creature_count;
    const spawn_entry_t *item_table;
    uint8_t item_count;
    uint8_t min_monsters;
    uint8_t max_monsters;
    uint8_t min_items;
    uint8_t max_items;
} depth_tier_t;

/***************************************************
 * private variables
 * ***************************************************/

/* Tier 1 (Depth 0-2): Surface levels - easy */
static const spawn_entry_t tier1_creatures[] = {
    { CREATURE_RAT,      80, 1, 1 },
    { CREATURE_COMMONER, 20, 1, 1 }
};

static const spawn_entry_t tier1_items[] = {
    { ITEM_BREAD,              25, 1, 1 },
    { ITEM_POTION_OF_HEALING,  25, 1, 1 },
    { ITEM_CLUB,               15, 1, 1 },
    { ITEM_STONE,              15, 3, 6 },
    { ITEM_SHORT_SWORD,        10, 1, 1 },
    { ITEM_LEATHER_ARMOUR,      5, 1, 1 },
    { ITEM_ARROW,               3, 3, 8 },
    { ITEM_SHORT_BOW,           1, 1, 1 },
    { ITEM_SHIELD,              1, 1, 1 }
};

/* Tier 2 (Depth 3-5): Mid levels - intermediate */
static const spawn_entry_t tier2_creatures[] = {
    { CREATURE_RAT,         60, 1, 1 },
    { CREATURE_WITHERWEED,  40, 1, 1 },
    { CREATURE_COMMONER,    30, 1, 1 }
};

static const spawn_entry_t tier2_items[] = {
    { ITEM_POTION_OF_HEALING,  30, 1, 1 },
    { ITEM_BREAD,              20, 1, 1 },
    { ITEM_ARROW,              15, 3, 8 },
    { ITEM_SHORT_SWORD,        12, 1, 1 },
    { ITEM_SHORT_BOW,           8, 1, 1 },
    { ITEM_LEATHER_ARMOUR,      7, 1, 1 },
    { ITEM_SHIELD,              5, 1, 1 },
    { ITEM_RING_OF_STRENGTH,    2, 1, 1 },
    { ITEM_CLUB,                1, 1, 1 }
};

/* Tier 3 (Depth 6+): Deep levels - dangerous */
static const spawn_entry_t tier3_creatures[] = {
    { CREATURE_WITHERWEED,  60, 1, 1 },
    { CREATURE_RAT,         25, 1, 1 },
    { CREATURE_COMMONER,    15, 1, 1 }
};

static const spawn_entry_t tier3_items[] = {
    { ITEM_POTION_OF_HEALING,  35, 1, 2 },
    { ITEM_SHORT_SWORD,        15, 1, 1 },
    { ITEM_ARROW,              12, 5, 10 },
    { ITEM_LEATHER_ARMOUR,     10, 1, 1 },
    { ITEM_RING_OF_STRENGTH,    8, 1, 1 },
    { ITEM_SHORT_BOW,           7, 1, 1 },
    { ITEM_SHIELD,              7, 1, 1 },
    { ITEM_BREAD,               5, 1, 1 },
    { ITEM_BOLT,                1, 3, 8 }
};

/* Depth tier configuration array */
static const depth_tier_t depth_tiers[] = {
    { tier1_creatures, 2, tier1_items, 9, 1, 2, 3, 5 },  /* Tier 0: depth 0-2 */
    { tier2_creatures, 3, tier2_items, 9, 2, 3, 4, 6 },  /* Tier 1: depth 3-5 */
    { tier3_creatures, 3, tier3_items, 9, 2, 4, 5, 8 }   /* Tier 2: depth 6+ */
};

/***************************************************
 * private function prototypes
 ***************************************************/
static void dungeon_place_player(dungeon_transition_t *c);
static void dungeon_restore_peristent_entities(dungeon_transition_t *c);

/* Spawn system helpers */
static uint8_t get_depth_tier(uint8_t depth);
static uint8_t select_from_table(const spawn_entry_t *table, uint8_t count);
static bool room_has_monster(const Room *r);
static void spawn_single_monster(const depth_tier_t *tier);
static void spawn_single_item(const depth_tier_t *tier);
static void spawn_monsters_for_depth(const depth_tier_t *tier, uint8_t count);
static void spawn_items_for_depth(const depth_tier_t *tier, uint8_t count);
static void spawn_special_content(dungeon_transition_t *c);

/***************************************************
 * public functions
 ***************************************************/
void dungeon_spawn_contents(dungeon_transition_t *c)
{
    uint8_t tier_idx;
    const depth_tier_t *tier;
    uint8_t num_monsters, num_items;

    /* Get appropriate tier for this depth */
    tier_idx = get_depth_tier(c->to_depth);
    tier = &depth_tiers[tier_idx];

    /* Calculate spawn counts (with randomness) */
    num_monsters = tier->min_monsters +
                   (rand() % (tier->max_monsters - tier->min_monsters + 1));
    num_items = tier->min_items +
                (rand() % (tier->max_items - tier->min_items + 1));

    /* Spawn content */
    spawn_monsters_for_depth(tier, num_monsters);
    spawn_items_for_depth(tier, num_items);

    /* Guaranteed/special content */
    spawn_special_content(c);
}

void dungeon_place_persistents(dungeon_transition_t *c)
{
   dungeon_place_player(c);
   dungeon_restore_peristent_entities(c);
}

/***************************************************
 * private functions
 ***************************************************/

/* Get tier index (0-2) based on depth */
static uint8_t get_depth_tier(uint8_t depth)
{
    if (depth <= 2) return 0;  /* Tier 1: Surface */
    if (depth <= 5) return 1;  /* Tier 2: Mid-levels */
    return 2;                   /* Tier 3: Deep */
}

/* Weighted random selection from spawn table */
static uint8_t select_from_table(const spawn_entry_t *table, uint8_t count)
{
    uint16_t total_weight = 0;
    uint16_t roll, cumulative;
    uint8_t i;

    /* Calculate total weight */
    for (i = 0; i < count; i++)
        total_weight += table[i].weight;

    /* Roll random value */
    roll = rand() % total_weight;

    /* Find selected entry */
    cumulative = 0;
    for (i = 0; i < count; i++)
    {
        cumulative += table[i].weight;
        if (roll < cumulative)
            return table[i].kind;
    }

    /* Fallback (should never reach) */
    return table[0].kind;
}

/* Check if room already has a monster */
static bool room_has_monster(const Room *r)
{
    entity_id_t i;

    for (i = 0; i < MAX_ENTITIES; i++)
    {
        if (!entity_has_flag(i, FLAG_IN_USE))
            continue;

        if (!entity_has_component(i, COMPONENT_CREATURE))
            continue;

        if (!entity_has_component(i, COMPONENT_LOCATION))
            continue;

        /* Check if creature is within room bounds */
        if (g.location_components[i].coord.x >= r->x &&
            g.location_components[i].coord.x < r->x + r->w &&
            g.location_components[i].coord.y >= r->y &&
            g.location_components[i].coord.y < r->y + r->h)
        {
            return true;
        }
    }

    return false;
}

/* Spawn a single monster in a random unoccupied room */
static void spawn_single_monster(const depth_tier_t *tier)
{
    Room *spawn_room;
    int spawn_x, spawn_y;
    uint8_t creature_kind;
    entity_id_t monster;
    uint8_t attempts;

    /* Select creature type from table */
    creature_kind = select_from_table(tier->creature_table, tier->creature_count);

    /* Find a room without a monster (max 20 attempts) */
    for (attempts = 0; attempts < 20; attempts++)
    {
        spawn_room = pick_random_room();
        if (!spawn_room)
            return;  /* No rooms available */

        if (!room_has_monster(spawn_room))
            break;
    }

    if (!spawn_room)
        return;

    /* Get random position in room */
    random_point_in_room(spawn_room, &spawn_x, &spawn_y);

    /* Create and place monster */
    monster = system_monster_create(creature_kind);
    if (monster != ENTITY_ID_INVALID)
        world_attach_entity(monster, spawn_x, spawn_y);
}

/* Spawn a single item in a random room */
static void spawn_single_item(const depth_tier_t *tier)
{
    Room *spawn_room;
    int spawn_x, spawn_y;
    uint8_t item_kind, quantity;
    const spawn_entry_t *entry;
    entity_id_t item;
    uint8_t i;

    /* Select item type from table */
    item_kind = select_from_table(tier->item_table, tier->item_count);

    /* Find the entry to get quantity range */
    entry = NULL;
    for (i = 0; i < tier->item_count; i++)
    {
        if (tier->item_table[i].kind == item_kind)
        {
            entry = &tier->item_table[i];
            break;
        }
    }

    if (!entry)
        return;

    /* Calculate quantity */
    if (entry->max_qty > entry->min_qty)
        quantity = entry->min_qty + (rand() % (entry->max_qty - entry->min_qty + 1));
    else
        quantity = entry->min_qty;

    /* Pick random room */
    spawn_room = pick_random_room();
    if (!spawn_room)
        return;

    /* Get random position in room */
    random_point_in_room(spawn_room, &spawn_x, &spawn_y);

    /* Create and place item */
    item = system_item_create(item_kind, quantity);
    if (item != ENTITY_ID_INVALID)
        world_attach_entity(item, spawn_x, spawn_y);
}

/* Spawn N monsters for this depth */
static void spawn_monsters_for_depth(const depth_tier_t *tier, uint8_t count)
{
    uint8_t i;

    for (i = 0; i < count; i++)
        spawn_single_monster(tier);
}

/* Spawn N items for this depth */
static void spawn_items_for_depth(const depth_tier_t *tier, uint8_t count)
{
    uint8_t i;

    for (i = 0; i < count; i++)
        spawn_single_item(tier);
}

/* Spawn guaranteed/special content */
static void spawn_special_content(dungeon_transition_t *c)
{
    Room *spawn_room;
    int spawn_x, spawn_y;
    entity_id_t potion;
    entity_id_t ring;

    /* Always spawn at least 1 healing potion */
    spawn_room = pick_random_room();
    if (spawn_room)
    {
        random_point_in_room(spawn_room, &spawn_x, &spawn_y);
        potion = system_item_create(ITEM_POTION_OF_HEALING, 1);
        if (potion != ENTITY_ID_INVALID)
            world_attach_entity(potion, spawn_x, spawn_y);
    }

    /* TODO: Spawn keys if locked doors exist */
    /* TODO: 10% chance monsters carry items */

    /* DEBUG - force spawning for testing*/
    ring = system_item_create(ITEM_RING_OF_STRENGTH, 1);
    if (ring != ENTITY_ID_INVALID)
    {
            world_attach_entity(ring, 22, 20);
    }
}

static void dungeon_place_player(dungeon_transition_t *c)
{
    uint8_t spawn_x;  
    uint8_t spawn_y;
    entity_id_t stair_entity = ENTITY_ID_INVALID;
    transistion_kind_t target_stair_kind;

    // Determine which stair to spawn at based on entry type
    // Descended (went down) → spawn at up stairs
    // Ascended (went up) → spawn at down stairs
    if (c->entry_kind == TRANSITION_DOWN)
    {
        target_stair_kind = TRANSITION_UP;
    }
    else if (c->entry_kind == TRANSITION_UP)
    {
        target_stair_kind = TRANSITION_DOWN;
    }
    else
    {
        // Teleport, new game, or other - pick a random location in a random room
        random_point_in_room(pick_random_room(), &spawn_x, &spawn_y);
        world_attach_entity(g.player.id, spawn_x, spawn_y);
        return;
    }

    // Find the appropriate stair entity
    for (entity_id_t i = 0; i < MAX_ENTITIES; i++)
    {
        if (!entity_has_flag(i, FLAG_IN_USE))
            continue;

        if (!entity_has_component(i, COMPONENT_TRANSITION))
            continue;

        if (g.transition_components[i].kind == target_stair_kind)
        {
            stair_entity = i;
            break;  // Found it
        }
    }

    // If stair found, use its coordinates; otherwise use default
    if (stair_entity != ENTITY_ID_INVALID &&
        entity_has_component(stair_entity, COMPONENT_LOCATION))
    {
        spawn_x = g.location_components[stair_entity].coord.x;
        spawn_y = g.location_components[stair_entity].coord.y;
    }

    world_attach_entity(g.player.id, spawn_x, spawn_y);
}

static void dungeon_restore_peristent_entities(dungeon_transition_t *c)
{
   
}