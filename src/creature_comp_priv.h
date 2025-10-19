/**
 * @file creature_comp_priv.h
 * @brief Private/internal declarations for creature_comp.c
 *
 * This header exposes internal creature definitions only to files that need them
 * (primarily `creature_comp.c` and systems that operae on creatures). It should NOT be included by general modules.
 */

#ifndef CREATURE_COMP_PRIV_H
#define CREATURE_COMP_PRIV_H

#include <stdint.h>

#include "creature_comp.h"
#include "entity_priv.h"

#include "zxnext.h"

/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 ***************************************************/

typedef enum {
    CREATURE_CLASS_NONE = 0,
    CREATURE_CLASS_ABERRATIONS,
    CREATURE_CLASS_BEASTS,
    CREATURE_CLASS_CELESTIALS,
    CREATURE_CLASS_CONSTRUCTS,
    CREATURE_CLASS_DRAGONS,
    CREATURE_CLASS_ELEMENTALS,
    CREATURE_CLASS_FEY,
    CREATURE_CLASS_FIENDS,
    CREATURE_CLASS_GIANTS,
    CREATURE_CLASS_HUMANOIDS,
    CREATURE_CLASS_MONSTROSITIES,
    CREATURE_CLASS_OOZES,
    CREATURE_CLASS_PLANTS,
    CREATURE_CLASS_UNDEAD
} creature_class_t;

typedef struct dice_s {
    uint8_t n;
    uint8_t d;
    uint8_t mod;
} dice_t;

typedef enum {
    DAMAGE_NONE, 
    DAMAGE_ACID,
    DAMAGE_BLUDGEONING,
    DAMAGE_COLD, 
    DAMAGE_FIRE, 
    DAMAGE_LIGHTNING, 
    DAMAGE_PIERCING, 
    DAMAGE_POISON, 
    DAMAGE_SLASHING
} damage_type_t;

typedef struct creature_attack_s {
    struct dice_s damage_roll;
    damage_type_t damage_type;
    uint8_t range; 
} creature_attack_t;

/* Creature type base attributes - read only  */
typedef struct {
    const char *name;
    zxnext_tile_t tile;
    creature_class_t c_class;
    uint8_t ac;
    uint8_t hp;
    uint8_t speed;
    uint8_t str;
    uint8_t dex;
    uint8_t con;
    uint8_t inte;
    uint8_t wis;
    uint8_t cha;
    uint8_t challenge;
    struct creature_attack_s melee;
    struct creature_attack_s ranged;
} creature_comp_base_t;


/* Creature component data per entity */
typedef struct {
    creature_kind_t kind;   // index into creature_comp_bases[]
    // variable data
    uint8_t ac;
    uint8_t cur_hp;
    uint8_t max_hp;
    uint8_t speed;
    uint8_t str;
    uint8_t dex;
    uint8_t con;
    uint8_t inte;
    uint8_t wis;
    uint8_t cha;
    struct creature_attack_s melee;
    struct creature_attack_s ranged;    
    // etc
} creature_comp_t;

typedef creature_comp_t creature_components_t[MAX_ENTITIES]; /* creature component data */



#endif /* CREATURE_COMP_PRIV_H */

