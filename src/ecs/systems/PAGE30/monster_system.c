/**
 * @file monster_system.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "monster_system.h"

#include "../../components/creature_comp.h"
#include "../../components/creature_comp_priv.h"


#include "../../../game/global_state.h"

#include "../../../core/util.h"
#include "../../../core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const monster_base_t monster_bases[CREATURE_KIND_COUNT] = {
   
    [CREATURE_NONE] = {.name = "None", .tile = {' ', 0}, .c_class = CREATURE_CLASS_NONE, .ac = 0, .hp = 0, .speed = SPEED_NONE, .str = 0, .dex = 0, .con = 0, .inte = 0, .wis = 0, .cha = 0, .challenge = 0, 
    .melee = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
   /* MONSTER_CLASS_ABERRATIONS */
   /* MONSTER_CLASS_BEASTS */
    [CREATURE_RAT] = {.name = "Rat", .tile = {'R', 0}, .c_class = CREATURE_CLASS_BEASTS, .ac = 10, .hp = 1, .speed = SPEED_30FT, .str = 2, .dex = 11, .con = 9, .inte = 2, .wis = 10, .cha = 4, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_PIERCING, .range = 1, .to_hit = 4, .to_damage = 2},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},

   /* MONSTER_CLASS_CELESTIALS */
   /* MONSTER_CLASS_CONSTRUCTS */
   /* MONSTER_CLASS_DRAGONS */
   /* MONSTER_CLASS_ELEMENTALS */
   /* MONSTER_CLASS_FEY */
   /* MONSTER_CLASS_FIENDS */
   /* MONSTER_CLASS_GIANTS */
   /* MONSTER_CLASS_HUMANOIDS */
    [CREATURE_COMMONER] = {.name = "Commoner", .tile = {'H', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
    [CREATURE_PLAYER] = {.name = "You", .tile = {'@', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},    

    /* MONSTER_CLASS_MONSTROSITIES */
    /* MONSTER_CLASS_OOZES */
    /* MONSTER_CLASS_PLANTS */
    [CREATURE_WITHERWEED] = {.name = "Witherweed", .tile = {'P', 0}, .c_class = CREATURE_CLASS_PLANTS, .ac = 5, .hp = 22, .speed = SPEED_5FT, .str = 3, .dex = 1, .con = 10, .inte = 1, .wis = 3, .cha = 1, .challenge = 100, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_POISON, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},    

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
    if (creature_add(id) == 0) {
        entity_destroy(id);
        return ENTITY_ID_INVALID;
    }

    g.creature_components[id].kind = kind;
    g.creature_components[id].ac = monster_bases[kind].ac;
    g.creature_components[id].max_hp = monster_bases[kind].hp;
    g.creature_components[id].cur_hp = monster_bases[kind].hp;
    g.creature_components[id].speed = monster_bases[kind].speed;
    g.creature_components[id].str = monster_bases[kind].str;
    g.creature_components[id].dex = monster_bases[kind].dex;
    g.creature_components[id].con = monster_bases[kind].con;
    g.creature_components[id].inte = monster_bases[kind].inte;
    g.creature_components[id].wis = monster_bases[kind].wis;
    g.creature_components[id].cha = monster_bases[kind].cha;
    g.creature_components[id].melee = monster_bases[kind].melee;
    g.creature_components[id].ranged = monster_bases[kind].ranged;    

    /* Add renderable component - use creature tile */
    monster_system_get_tile(id, &tile);
    if(renderable_add(id, &tile) == 0) {
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
