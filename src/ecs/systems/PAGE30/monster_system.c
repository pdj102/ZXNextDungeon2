/**
 * @file monster_system.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "monster_system.h"

#include "ecs/components/components.h"
#include "ecs/components/PAGE50/name_comp.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/

const stats_comp_t monster_stats_base[CREATURE_KIND_COUNT] =
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

const destructible_comp_t monster_destructible_base[CREATURE_KIND_COUNT] =
{
    [CREATURE_NONE] = {.ac = 0, .cur_hp = 0, .max_hp = 0, .immune = DAMAGE_KIND_NONE, .resist = DAMAGE_KIND_NONE, .vulnerable = DAMAGE_KIND_NONE},
   /* MONSTER_CLASS_ABERRATIONS */ 
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.ac = 10, .cur_hp = 1, .max_hp = 1, .immune = DAMAGE_KIND_NONE, .resist = DAMAGE_KIND_NONE, .vulnerable = DAMAGE_KIND_NONE},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.ac = 10, .cur_hp = 4, .max_hp = 4, .immune = DAMAGE_KIND_NONE, .resist = DAMAGE_KIND_NONE, .vulnerable = DAMAGE_KIND_NONE},
    [CREATURE_PLAYER] = {.ac = 10, .cur_hp = 4, .max_hp = 4, .immune = DAMAGE_KIND_NONE, .resist = DAMAGE_KIND_NONE, .vulnerable = DAMAGE_KIND_NONE},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.ac = 5, .cur_hp = 22, .max_hp = 22, .immune = DAMAGE_KIND_BLUDGEONING, .resist = DAMAGE_KIND_NONE, .vulnerable = DAMAGE_KIND_NONE}
    /* MONSTER_CLASS_UNDEAD */    
};


/* Monster default melee attack*/
 const attack_comp_t monster_melee_base[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE] = {.attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.attack_type = ATTACK_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_KIND_PIERCING, .range = 1, .hit_mod = 4, .damage_mod = 2},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.attack_type = ATTACK_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_KIND_BLUDGEONING, .range = 1, .hit_mod = 2, .damage_mod = 0},
    [CREATURE_PLAYER] = {.attack_type = ATTACK_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_KIND_BLUDGEONING, .range = 1, .hit_mod = 0, .damage_mod = 0},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.attack_type = ATTACK_MELEE, .damage_roll = DICE_1D4, .damage_kind = DAMAGE_KIND_POISON, .range = 1, .hit_mod = 2, .damage_mod = 0},
    /* MONSTER_CLASS_UNDEAD */    
};

/* Monster default ranged attack*/
 const attack_comp_t monster_ranged_base[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE] = {.attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    [CREATURE_PLAYER] = { .attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.attack_type = ATTACK_NONE, .damage_roll = DICE_NONE, .damage_kind = DAMAGE_KIND_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    /* MONSTER_CLASS_UNDEAD */    
};

const uint8_t monster_challenge_base[CREATURE_KIND_COUNT] = 
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

const name_id_t creature_name_base[CREATURE_KIND_COUNT] = 
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

const renderable_comp_t monster_renderable_base[CREATURE_KIND_COUNT] = 
{
    [CREATURE_NONE] = { .tile = {' ', 0}},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */      
    [CREATURE_RAT] = { .tile = { 'R', 0}},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = { .tile = { 'H', 0}},
    [CREATURE_PLAYER] = { .tile = { '@', 0}},
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = { .tile = { 'P', 0}}
    /* MONSTER_CLASS_UNDEAD */    
};

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
    comp_creature_add(id, kind);

    /* Add stat block */
    comp_stats_add(id, monster_stats_base[kind]);

    /* If monster has melee attack add */
    if (monster_melee_base[kind].attack_type == ATTACK_MELEE)
    {
        comp_melee_add(id, monster_melee_base[kind]);
    }

    /* If monster has ranged attack add */
    if (monster_ranged_base[kind].damage_kind == ATTACK_RANGED)
    {
        comp_ranged_add(id, monster_ranged_base[kind]);
    }

    /* If moster is destructible add (indicated by AC > 0) */
    if (monster_destructible_base[kind].ac > 0 )
    {
        comp_destructible_add(id, monster_destructible_base[kind]);
    }

    /* Add renderable component  */
    comp_renderable_add(id, monster_renderable_base[kind].tile);

    /* Add container component */
    comp_container_add(id);
  
    /* Add timer component*/
    comp_timer_add(id, speed_to_ticks(monster_stats_base[kind].speed ));

    /* All monsters have a name component*/
    comp_name_add(id, creature_name_base[kind]);

    return id;
}

entity_id_t monster_system_create_player( void )
{
    entity_id_t id = monster_system_create(CREATURE_PLAYER);
    if (id == ENTITY_ID_INVALID)
        return ENTITY_ID_INVALID;

    /* Add player control component */
    g.player.id = id;
    comp_player_add(id);

    /* Add slots component */
    comp_slots_add(id);

    return id;
}


