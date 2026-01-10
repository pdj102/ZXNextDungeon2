/**
 * @file monster_system.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "monster_system.h"

#include "ecs/components/components.h"
#include "ecs/components/name_comp.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/

static const stats_comp_t monster_stats_base[CREATURE_KIND_COUNT] =
{
    [CREATURE_NONE] = {.speed = SPEED_NONE, .stats = {0, 0, 0, 0, 0, 0}},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.speed = SPEED_30FT, .stats = {2, 11, 9, 2, 10, 4}},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.speed = SPEED_30FT, .stats = {10, 10, 10, 10, 10, 10 }},
    [CREATURE_PLAYER] = {.speed = SPEED_30FT, .stats = {10, 10, 10, 10, 10, 10 }},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.speed = SPEED_5FT, .stats = {3, 1, 10, 1, 3, 1 }}
    /* MONSTER_CLASS_UNDEAD */    
};

static const destructible_comp_t monster_destructible_base[CREATURE_KIND_COUNT] =
{
    [CREATURE_NONE] = {.ac = 0, .cur_hp = 0, .max_hp = 0, .immune = DAMAGE_NONE, .resist = DAMAGE_NONE, .vulnerable = DAMAGE_NONE},
   /* MONSTER_CLASS_ABERRATIONS */ 
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.ac = 10, .cur_hp = 1, .max_hp = 1, .immune = DAMAGE_NONE, .resist = DAMAGE_NONE, .vulnerable = DAMAGE_NONE},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.ac = 10, .cur_hp = 4, .max_hp = 4, .immune = DAMAGE_NONE, .resist = DAMAGE_NONE, .vulnerable = DAMAGE_NONE},
    [CREATURE_PLAYER] = {.ac = 10, .cur_hp = 12, .max_hp = 4, .immune = DAMAGE_NONE, .resist = DAMAGE_NONE, .vulnerable = DAMAGE_NONE},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.ac = 5, .cur_hp = 22, .max_hp = 22, .immune = DAMAGE_BLUDGEONING, .resist = DAMAGE_NONE, .vulnerable = DAMAGE_NONE}
    /* MONSTER_CLASS_UNDEAD */    
};


/* Monster default melee attack*/
 static const attack_comp_t monster_melee_base[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE] = {.attack_type = ATTACK_KIND_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_PIERCING, .range = 1, .hit_mod = 4, .damage_mod = 2},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 2, .damage_mod = 0},
    [CREATURE_PLAYER] = {.attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.attack_type = ATTACK_KIND_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_POISON, .range = 1, .hit_mod = 2, .damage_mod = 0},
    /* MONSTER_CLASS_UNDEAD */    
};

/* Monster default ranged attack*/
 static const attack_comp_t monster_ranged_base[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE] = {.attack_type = ATTACK_KIND_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.attack_type = ATTACK_KIND_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.attack_type = ATTACK_KIND_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    [CREATURE_PLAYER] = { .attack_type = ATTACK_KIND_RANGED, .damage_roll = DICE_1D8, .damage_kind = DAMAGE_PIERCING, .range = 5, .hit_mod = 0, .damage_mod = 0, .allowed_ammo = AMMO_NONE},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.attack_type = ATTACK_KIND_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* MONSTER_CLASS_UNDEAD */    
};

static const uint8_t monster_challenge_base[CREATURE_KIND_COUNT] = 
{
    [CREATURE_NONE] = 0,
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    [CREATURE_RAT] = 10,
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = 10,
    [CREATURE_PLAYER] = 10,
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = 100
    /* MONSTER_CLASS_UNDEAD */    
};

static const name_id_t creature_name_base[CREATURE_KIND_COUNT] = 
{
    [CREATURE_NONE] = NAME_NONE,
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    [CREATURE_RAT] = NAME_RAT,
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = NAME_COMMONER,
    [CREATURE_PLAYER] = NAME_PLAYER,
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = NAME_WITHERWEED
    /* MONSTER_CLASS_UNDEAD */
};

static const renderable_comp_t monster_renderable_base[CREATURE_KIND_COUNT] = 
{
    [CREATURE_NONE] = { .tile = {' ', 0}},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    [CREATURE_RAT] = { .tile = { 'R', PALETTE_BROWN}},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = { .tile = { 'H', PALETTE_WHITE}},
    [CREATURE_PLAYER] = { .tile = { '@', 16}},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = { .tile = { 'P', PALETTE_WHITE}}
    /* MONSTER_CLASS_UNDEAD */    
};


/* Speed into turns and ticks conversion table (rounded)
| Speed (ft/turn) | Turns | Ticks (0–9) | Total Ticks   | Relative to Human (30 ft) |
| --------------- | ----- | ----------- | -----------   | ------------------------- |
| 5               | 6     | 0           | 60            |~6× slower                 |
| 10              | 3     | 0           | 30            | ~3× slower                |
| 15              | 2     | 0           | 20            | ~2× slower                |
| 20              | 1     | 5           | 15            | 1.5× slower               |
| 25              | 1     | 2           | 12            | 1.2× slower               |
| 30              | 1     | 0           | 10            | baseline                  |
| 35              | 0     | 9           |  9            | 1.15× faster              |
| 40              | 0     | 8           |  8            | 1.3× faster               |
| 45              | 0     | 7           |  7            | 1.5× faster               |
| 50              | 0     | 6           |  6            | 1.6× faster               |
| 55              | 0     | 5           |  5            | 1.8× faster               |
| 60              | 0     | 4           |  4            | ~2× faster                |
*/
static const ticks_t speed_to_ticks_table[SPEED_COUNT] = {
   [SPEED_NONE] = 0,
   [SPEED_5FT]  = 60,
   [SPEED_10FT] = 30,
   [SPEED_15FT] = 20,
   [SPEED_20FT] = 15,
   [SPEED_25FT] = 12,
   [SPEED_30FT] = 10,
   [SPEED_35FT] = 9,
   [SPEED_40FT] = 8,
   [SPEED_45FT] = 7,
   [SPEED_50FT] = 6,
   [SPEED_55FT] = 5,
   [SPEED_60FT] = 4
};

/***************************************************
 * private function prototypes
 ****************************************************/
static void melee_add(entity_id_t entity, const attack_comp_t *attack);
static void ranged_add(entity_id_t entity, const attack_comp_t *attack);
static uint8_t creature_add(entity_id_t entity, creature_kind_t kind);
static void creature_remove(entity_id_t entity);
static void add_destructible(entity_id_t entity, const destructible_comp_t *destructible);
static void add_stats(entity_id_t entity, const stats_comp_t *stats);
static ticks_t speed_to_ticks(speed_t speed);
static void add_container(entity_id_t entity);
static void add_timer(entity_id_t entity, ticks_t ticks);
static void add_name(entity_id_t entity, name_id_t name);
static void add_active_effects(entity_id_t entity);
void add_slots(entity_id_t id);

/***************************************************
 * public functions
 ***************************************************/

 void monster_system_init(void)
 {
   /*

   */
 }

 entity_id_t monster_system_create(creature_kind_t kind)
{
    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
    {
        util_abort("");         
        return ENTITY_ID_INVALID;
    }

    entity_set_flag(id, FLAG_BLOCKING);   

    /* Add creature component */
    creature_add(id, kind);

    /* Add stat block */
    add_stats(id, &monster_stats_base[kind]);

    /* If monster has melee attack add */
    if (monster_melee_base[kind].attack_type == ATTACK_KIND_MELEE)
    {
        melee_add(id, &monster_melee_base[kind]);
    }

    /* If monster has ranged attack add */
    if (monster_ranged_base[kind].attack_type == ATTACK_KIND_RANGED)
    {
        ranged_add(id, &monster_ranged_base[kind]);
    }

    /* If moster is destructible add (indicated by AC > 0) */
    if (monster_destructible_base[kind].ac > 0 )
    {
        add_destructible(id, &monster_destructible_base[kind]);
    }

    /* Add renderable component  */
    entity_set_component(id, COMPONENT_RENDERABLE);
    g.renderable_components[id].tile = monster_renderable_base[kind].tile;

    /* Add container component */
    add_container(id);
  
    /* Add timer component*/
    add_timer(id, speed_to_ticks(monster_stats_base[kind].speed));

    /* All monsters have a name component*/
    add_name(id, creature_name_base[kind]);

    /* All monsters have an active effects component*/
    entity_set_component(id, COMPONENT_ACTIVE_EFFECT);

    /* Add an AI component*/
    entity_set_component(id, COMPONENT_AI);
    g.ai_components[id].state = AI_STATE_IDLE;    

    return id;
}

entity_id_t monster_system_create_player( void )
{
    entity_id_t id = monster_system_create(CREATURE_PLAYER);

    if (id == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;

    g.player.id = id;
    
    entity_set_flag(id, FLAG_PERSISTANT);  

    /* Remove AI component */
    entity_clear_component(id, COMPONENT_AI);

    /* Add player control component */
    g.player.id = id;
    entity_set_component(id, COMPONENT_PLAYER);

    /* Add slots component */
    add_slots(id);    

    return id;
}

/***************************************************
 * private functions
 ****************************************************/
static void melee_add(entity_id_t entity, const attack_comp_t *attack)
{
    g.melee_components[entity].damage_kind = attack->damage_kind;
    g.melee_components[entity].damage_roll = attack->damage_roll;
    g.melee_components[entity].damage_mod = attack->damage_mod;
    g.melee_components[entity].hit_mod = attack->hit_mod;
    g.melee_components[entity].range = attack->range;

    entity_set_component(entity, COMPONENT_MELEE_ATTACK);
}

static void ranged_add(entity_id_t entity, const attack_comp_t *attack)
{
    g.ranged_components[entity].damage_kind = attack->damage_kind;
    g.ranged_components[entity].damage_roll = attack->damage_roll;
    g.ranged_components[entity].damage_mod = attack->damage_mod;
    g.ranged_components[entity].hit_mod = attack->hit_mod;
    g.ranged_components[entity].range = attack->range;

    entity_set_component(entity, COMPONENT_RANGED_ATTACK);
}

static uint8_t creature_add(entity_id_t entity, creature_kind_t kind)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CREATURE)); /* entity must not have creature component */

    g.creature_components[entity].kind = kind; 
    g.creature_components[entity].status = CREATURE_STATUS_ALIVE; 

    entity_set_component(entity, COMPONENT_CREATURE); 

    return 1; /* success */
}

static void creature_remove(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    if (!entity_has_component(entity, COMPONENT_CREATURE))
    {
        return;
    }

    entity_clear_component(entity, COMPONENT_CREATURE); /* clear entity creature component mask */
}

static void add_destructible(entity_id_t entity, const destructible_comp_t *destructible)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_DESTRUCTIBLE)); 

    g.destructible_components[entity].ac = destructible->ac;
    g.destructible_components[entity].cur_hp = destructible->cur_hp;
    g.destructible_components[entity].max_hp = destructible->max_hp;
    g.destructible_components[entity].immune = destructible->immune;
    g.destructible_components[entity].resist = destructible->resist;
    g.destructible_components[entity].vulnerable = destructible->vulnerable;

    entity_set_component(entity, COMPONENT_DESTRUCTIBLE); 
}

static void add_stats(entity_id_t entity, const stats_comp_t *stats)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_STATS)); /* entity must not have creature component */

    g.stats_components[entity].speed = speed_to_ticks_table[stats->speed];
    g.stats_components[entity].stats[STAT_STR] = stats->stats[STAT_STR];
    g.stats_components[entity].stats[STAT_DEX] = stats->stats[STAT_DEX];
    g.stats_components[entity].stats[STAT_CON] = stats->stats[STAT_CON];
    g.stats_components[entity].stats[STAT_INT] = stats->stats[STAT_INT];
    g.stats_components[entity].stats[STAT_WIS] = stats->stats[STAT_WIS];
    g.stats_components[entity].stats[STAT_CHA] = stats->stats[STAT_CHA];

    entity_set_component(entity, COMPONENT_STATS); 
}

static ticks_t speed_to_ticks(speed_t speed)
{
    return speed_to_ticks_table[speed];
}

static void add_container(entity_id_t entity)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_CONTAINER)); /* entity must not have container component */

    g.container_components[entity].head = ENTITY_ID_INVALID; 
    g.container_components[entity].capacity = 10;
    g.container_components[entity].count = 0; 

    entity_set_component(entity, COMPONENT_CONTAINER); /* set entity container component mask */
}

static void add_timer(entity_id_t entity, ticks_t ticks)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_TIMER)); /* entity must not have timer component */

    /* Set timer */
    g.timer_components.timers[entity].base_ticks = ticks;
    g.timer_components.timers[entity].ticks = ticks; 
    g.timer_components.timers[entity].active = 1;
    g.timer_components.timers[entity].fired = 0;

    /* Add to active timer list*/
    g.timer_components.list[g.timer_components.count++] = entity;

    entity_set_component(entity, COMPONENT_TIMER); /* set entity timer component mask */ 
}

static void add_name(entity_id_t entity, name_id_t name)
{
    util_assert(entity < MAX_ENTITIES);
    util_assert(!entity_has_component(entity, COMPONENT_NAME));

    g.name_components[entity] = name; 

    entity_set_component(entity, COMPONENT_NAME);
}

void add_slots(entity_id_t id)
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