/**
 * @file monster_system.h
 * @author Paul Johnson
 * @brief 
 * 
 */

#ifndef MONSTER_SYSTEM_H
#define MONSTER_SYSTEM_H

#include "ecs/components/creature_comp.h"

#include "core/text.h"


/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/* Monster type base attributes - read only  */
typedef struct {
    const char *name;
    zxnext_tile_t tile;
    creature_class_t c_class;
    uint8_t ac;
    uint8_t hp;
    creature_speed_t speed;
    uint8_t str;
    uint8_t dex;
    uint8_t con;
    uint8_t inte;
    uint8_t wis;
    uint8_t cha;
    uint8_t challenge;
    struct creature_attack_s melee;
    struct creature_attack_s ranged;
} monster_base_t;

extern const monster_base_t monster_bases[];

/***************************************************
 * public function prototypes
 ***************************************************/

void monster_system_init(void);

entity_id_t monster_system_create(creature_kind_t kind);

entity_id_t monster_system_create_player( void );

void monster_system_print_name(text_window_t *win, creature_kind_t kind);

void monster_system_get_tile(entity_id_t id, zxnext_tile_t *tile);

#endif // MONSTER_SYSTEM_H
