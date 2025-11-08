/**
 * @file creature_base.c
 * @author Paul Johnson
 * @brief 
 * 
 */

#include "creature_base.h"

#include "../creature_comp.h"
#include "../creature_comp_priv.h"

#include "../../../game/global_state.h"

#include "../../../core/util.h"
#include "../../../core/zxnext.h"

/***************************************************
 * private variables
 * ***************************************************/
const creature_comp_base_t creature_bases[CREATURE_KIND_COUNT] = {
   
    [CREATURE_NONE] = {.name = "None", .tile = {' ', 0}, .c_class = CREATURE_CLASS_NONE, .ac = 0, .hp = 0, .speed = SPEED_NONE, .str = 0, .dex = 0, .con = 0, .inte = 0, .wis = 0, .cha = 0, .challenge = 0, 
    .melee = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
   /* CREATURE_CLASS_ABERRATIONS */
   /* CREATURE_CLASS_BEASTS */
    [CREATURE_RAT] = {.name = "Rat", .tile = {'R', 0}, .c_class = CREATURE_CLASS_BEASTS, .ac = 10, .hp = 1, .speed = SPEED_30FT, .str = 2, .dex = 11, .con = 9, .inte = 2, .wis = 10, .cha = 4, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_PIERCING, .range = 1, .to_hit = 4, .to_damage = 2},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},

   /* CREATURE_CLASS_CELESTIALS */
   /* CREATURE_CLASS_CONSTRUCTS */
   /* CREATURE_CLASS_DRAGONS */
   /* CREATURE_CLASS_ELEMENTALS */
   /* CREATURE_CLASS_FEY */
   /* CREATURE_CLASS_FIENDS */
   /* CREATURE_CLASS_GIANTS */
   /* CREATURE_CLASS_HUMANOIDS */
    [CREATURE_COMMONER] = {.name = "Commoner", .tile = {'H', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},
    [CREATURE_PLAYER] = {.name = "You", .tile = {'@', 0}, .c_class = CREATURE_CLASS_HUMANOIDS, .ac = 10, .hp = 4, .speed = SPEED_30FT, .str = 10, .dex = 10, .con = 10, .inte = 10, .wis = 10, .cha = 10, .challenge = 10, 
    .melee = { .damage_roll = DICE_1D8, .damage_type = DAMAGE_BLUDGEONING, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},    

    /* CREATURE_CLASS_MONSTROSITIES */
    /* CREATURE_CLASS_OOZES */
    /* CREATURE_CLASS_PLANTS */
    [CREATURE_WITHERWEED] = {.name = "Witherweed", .tile = {'P', 0}, .c_class = CREATURE_CLASS_PLANTS, .ac = 5, .hp = 22, .speed = SPEED_5FT, .str = 3, .dex = 1, .con = 10, .inte = 1, .wis = 3, .cha = 1, .challenge = 100, 
    .melee = { .damage_roll = DICE_1D4, .damage_type = DAMAGE_POISON, .range = 1, .to_hit = 2, .to_damage = 0},
    .ranged = { .damage_roll = DICE_NONE, .damage_type = DAMAGE_NONE, .range = 0, .to_hit = 0, .to_damage = 0}},    

    /* CREATURE_CLASS_UNDEAD */
};

 /* Speed into turns and ticks conversion table (rounded)
| Speed (ft/turn) | Turns | Ticks (0–9) | Relative to Human (30 ft) |
| --------------- | ----- | ----------- | ------------------------- |
| 5               | 6     | 0           | ~6× slower                |
| 10              | 3     | 0           | ~3× slower                |
| 15              | 2     | 0           | ~2× slower                |
| 20              | 1     | 5           | 1.5× slower               |
| 25              | 1     | 2           | 1.2× slower               |
| 30              | 1     | 0           | baseline                  |
| 35              | 0     | 9           | 1.15× faster              |
| 40              | 0     | 8           | 1.3× faster               |
| 45              | 0     | 7           | 1.5× faster               |
| 50              | 0     | 6           | 1.6× faster               |
| 55              | 0     | 5           | 1.8× faster               |
| 60              | 0     | 5           | 2× faster                 |
*/
const turn_tick_t creature_speeds_conversion[SPEED_COUNT] = {
   [SPEED_NONE] = {0, 0},
   [SPEED_5FT]  = {6, 0},
   [SPEED_10FT] = {3, 0},
   [SPEED_15FT] = {2, 0},
   [SPEED_20FT] = {1, 5},
   [SPEED_25FT] = {1, 2},
   [SPEED_30FT] = {1, 0},
   [SPEED_35FT] = {0, 9},
   [SPEED_40FT] = {0, 8},
   [SPEED_45FT] = {0, 7},
   [SPEED_50FT] = {0, 6},
   [SPEED_55FT] = {0, 5},
   [SPEED_60FT] = {0, 5}
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


