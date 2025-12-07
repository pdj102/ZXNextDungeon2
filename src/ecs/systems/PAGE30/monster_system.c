/**
 * @file monster_system.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "monster_system.h"

#include "ecs/components/creature_comp.h"

#include "game/global_state.h"

#include "core/util.h"
#include "core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/

const creature_stats_comp_t monster_stats_base[CREATURE_KIND_COUNT] =
{
    [CREATURE_NONE] = {.ac = 0, .cur_hp = 0, .max_hp = 0, .speed = SPEED_NONE, .str = 0, .dex = 0, .con = 0, .inte = 0, .wis = 0, .cha = 0},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */    
    [CREATURE_RAT] = {.ac = 10, .cur_hp = 1, .max_hp = 1, .speed = SPEED_30FT, .str = 2, .dex = 11, .con = 9, .inte = 2, .wis = 10, .cha = 4},
   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */    
    [CREATURE_COMMONER] = {.ac = 10, .cur_hp = 4, .max_hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10 },
    [CREATURE_PLAYER] = {.ac = 10, .cur_hp = 4, .max_hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10 },
    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */    
    [CREATURE_WITHERWEED] = {.ac = 5, .cur_hp = 22, .max_hp = 22, .speed = SPEED_5FT, .str = 3, .dex = 1, .con = 10, .inte = 1, .wis = 3, .cha = 1 }
    /* MONSTER_CLASS_UNDEAD */    
};


/* TODO Add monster_melee_base here*/
/* TODO Add monster_ranged_base here*/


 const monster_base_t monster_bases[CREATURE_KIND_COUNT] = {
   
    [CREATURE_NONE] = {.name = "None", .tile = {' ', 0}, .c_class = CREATURE_CLASS_NONE, .ac = 0, .hp = 0, .speed = SPEED_NONE, .str = 0, .dex = 0, .con = 0, .inte = 0, .wis = 0, .cha = 0, .challenge = 0, 
    .melee = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0}},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */
    [CREATURE_RAT] = {.name = "Rat", .tile = {'R', 0}, .c_class = CREATURE_CLASS_BEASTS, .ac = 10, .hp = 1, .speed = SPEED_30FT, .str = 2, .dex = 11, .con = 9, .inte = 2, .wis = 10, .cha = 4, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_PIERCING, .range = 1, .hit_mod = 4, .damage_mod = 2},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0}},

   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */
    [CREATURE_COMMONER] = {.name = "Commoner", .tile = {'H', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 2, .damage_mod = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0}},
    [CREATURE_PLAYER] = {.name = "You", .tile = {'@', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .hit_mod = 2, .damage_mod = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0}},    

    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */
    [CREATURE_WITHERWEED] = {.name = "Witherweed", .tile = {'P', 0}, .c_class = CREATURE_CLASS_PLANTS, .ac = 5, .hp = 22, .speed = SPEED_5FT, .str = 3, .dex = 1, .con = 10, .inte = 1, .wis = 3, .cha = 1, .challenge = 100, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_POISON, .range = 1, .hit_mod = 2, .damage_mod = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .hit_mod = 0, .damage_mod = 0}},    

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
    zxnext_tile_t tile; 

    entity_id_t id = entity_create();
    if (id == ENTITY_ID_INVALID)
        return id;

    entity_set_flag(id, FLAG_BLOCKING);

    /* Add creature component */
    if (creature_add(id, kind) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add stat block */
    if (stats_add(id))
    {
        entity_destroy(id);
        return ENTITY_ID_INVALID;       
    }
    /* Set stat block */
    g.creature_stat_components[id] = monster_stats_base[kind];

    /* Add renderable component  */
    if(renderable_add(id, monster_renderable_base[kind].tile) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    /* Add container component */
    if (container_add(id) == 0)
    {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }
  
    /* Add timer component*/
    if (timer_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }
    turn_tick_t tt;
    creature_speed_to_turns_ticks(id, &tt);
    text_printf(&g.msg_win, "turns:%u ticks:%u\n", tt.turns, tt.ticks);
    timer_set(id, tt.turns, tt.ticks);    

    return id;
}

entity_id_t monster_system_create_player( void )
{
  entity_id_t id = monster_system_create(CREATURE_PLAYER);
    if (id == ENTITY_ID_INVALID)
        return id;  

    /* Add player control component */
    if (player_ctrl_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    return id;
}

 void monster_system_print_name(text_window_t *win, creature_kind_t kind)
 {
    text_print_string(win, monster_bases[kind].name);
 }

void monster_system_get_tile(entity_id_t id, zxnext_tile_t *tile)
{
    tile->tile_attr = monster_bases[g.creature_components[id].kind].tile.tile_attr;
    tile->tile_id = monster_bases[g.creature_components[id].kind].tile.tile_id;
}
