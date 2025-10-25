/**
 * @file creature_base.c
 * @author Paul Johnson
 * @brief 
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma output CRT_ORG_PAGE_30 = 0xC000

#include "creature_base.h"

#include "../creature_comp.h"
#include "../creature_comp_priv.h"

#include "../../game/global_state.h"

#include "../../core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const creature_comp_base_t creature_bases[CREATURE_KIND_COUNT] = {
    [CREATURE_NONE] = {.name = "None", .tile = {' ', 0}, .c_class = CREATURE_CLASS_NONE, .ac = 0, .hp = 0, .speed = 0, .str = 0, .dex = 0, .con = 0, .inte = 0, .wis = 0, .cha = 0, .challenge = 0, 
    .melee = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
    
    [CREATURE_RAT] = {.name = "Rat", .tile = {'R', 0}, .c_class = CREATURE_CLASS_BEASTS, .ac = 10, .hp = 1, .speed = 15, .str = 2, .dex = 11, .con = 9, .inte = 2, .wis = 10, .cha = 4, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_PIERCING, .range = 1, .to_hit = 4, .to_damage = 2},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},

    [CREATURE_COMMONER] = {.name = "Commoner", .tile = {'H', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = 10, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
};

/***************************************************
 * public functions
 ***************************************************/

 void creature_base_init(uint8_t creature, uint8_t kind)
 {
    g.creature_components[creature].kind = kind;
    g.creature_components[creature].ac = creature_bases[kind].ac;
    g.creature_components[creature].max_hp = creature_bases[kind].hp;
    g.creature_components[creature].cur_hp = creature_bases[kind].hp;
    g.creature_components[creature].speed = creature_bases[kind].speed;
    g.creature_components[creature].str = creature_bases[kind].str;
    g.creature_components[creature].dex = creature_bases[kind].dex;
    g.creature_components[creature].con = creature_bases[kind].con;
    g.creature_components[creature].inte = creature_bases[kind].inte;
    g.creature_components[creature].wis = creature_bases[kind].wis;
    g.creature_components[creature].cha = creature_bases[kind].cha;
    g.creature_components[creature].melee = creature_bases[kind].melee;
    g.creature_components[creature].ranged = creature_bases[kind].ranged;
 }

 void creature_base_print_name(text_window_t *win, entity_id_t creature)
 {
    creature_kind_t kind = g.creature_components[creature].kind;
    text_print_string(win, creature_bases[kind].name);
 }