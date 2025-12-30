/**
 * @file game.h
 * @author Paul Johnson
 * @brief Roguelike game general data structures and constants.
 */

#ifndef GAME_H
#define GAME_H

#include <stdint.h>

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/
/*
 * Memory map - Next 8KB banking scheme
 *
 * slot 0 (0x000)     Fixed global game state (by default would contain the ROM)
 * slot 1 (0x2000)    Fixed global game state (by default would contain the ROM) 
 * slot 2 (0x4000)    Fixed tilemap and tilesets (bank 5)
 * slot 3 (0x6000)    Fixed tilemap and tilesets (bank 5)
 * slot 4 (0x8000)    Fixed non banking core game code (bank 2)
 * slot 5 (0xa000)    Fixed non banking core game code (bank 2)
 * slot 6 (0xc000)    Banked game code and data (bank 0) 
 * slot 7 (0xe000)    Banked game code and data (bank 0)
 *
 *
 * 0x4000 - 0x49FF      Tilemap - 40 * 32 tiles * 2 bytes per tile = 0xA00 (2,560) bytes
 * 0x4a00 - 0x69FF      Tele definitions - 256 tiles * 32 bytes per tile definition = 0x2000 (8,192) bytes
 * 0x6a00 - 0x7FFF      NOT USED
 * 
 * 0xbfff               Top of stack (TODO move stack to unused space at top of bank 5)
 * 0x7fff               Top of stack for bank 5 (does not work) 0x69FF
 */

 /*
  * Page numbers and usage
  *
  * NB 
  *     use even page numbers for default ORG 0xc000 e.g. page 30, 32
  *     use odd page numbers for default ORG 0xe000 e.g. page 31, 33
  */

#define PAGE_GLOBAL_STATE     28 
#define PAGE_GLOBAL_STATE_2   29 
#define PAGE_MONSTER_SYSTEM   30
#define PAGE_ITEM_SYSTEM      32
#define PAGE_DUNGEON_GEN      34
#define PAGE_INIT             36
#define PAGE_PALETTE          37
#define PAGE_TIMER_SYSTEM     38
#define PAGE_CONTAINER_SYSTEM 40
#define PAGE_EVENT_SYSTEM     42
#define PAGE_ACTIONS_SYSTEM   44
#define PAGE_PLAYER_SYSTEM    46
#define PAGE_EQUIPMENT_SYSTEM 48
#define PAGE_PERCEPTION_SYSTEM 50
#define PAGE_MOVEMENT_SYSTEM  52
#define PAGE_COMBAT_SYSTEM    54
#define PAGE_DAMAGE_SYSTEM    56
#define PAGE_STATS_SYSTEM     58
#define PAGE_EFFECT_SYSTEM_1  60
#define PAGE_EFFECT_SYSTEM_2  61
#define PAGE_CONSUMABLE_SYSTEM    62
#define PAGE_NAME_SYSTEM      64
#define PAGE_HEALING_SYSTEM   66
#define PAGE_UI               68
#define PAGE_AI               70

typedef enum direction_e {
    DIRECTION_NONE = 0,
    DIRECTION_NORTH,
    DIRECTION_WEST,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_COUNT
} direction_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} coord_t;

typedef struct {
    int8_t x;
    int8_t y;
} vector_t;

typedef enum dice_e {
    DICE_NONE = 0,
    DICE_1D4,
    DICE_1D6,
    DICE_1D8,
    DICE_1D10,
    DICE_1D20,
    DICE_COUNT
} dice_kind_t;

typedef struct dice_s {
    uint8_t n;
    uint8_t d;
    uint8_t mod;
} dice_roll_t;

typedef uint8_t ticks_t;

typedef enum {
    ATTACK_MISS,
    ATTACK_HIT,
    ATTACK_CRITICAL
} attack_result_t;

typedef enum {
    ATTACK_KIND_NONE,
    ATTACK_KIND_MELEE,
    ATTACK_KIND_RANGED,
    ATTACK_KIND_MAGIC
} attack_kind_t;

/* Damage type flags */
typedef enum {
    DAMAGE_NONE            = 0,
    DAMAGE_ACID            = 1 << 0,
    DAMAGE_BLUDGEONING     = 1 << 1,
    DAMAGE_COLD            = 1 << 2,
    DAMAGE_FIRE            = 1 << 3,
    DAMAGE_LIGHTNING       = 1 << 4,
    DAMAGE_PIERCING        = 1 << 5,
    DAMAGE_POISON          = 1 << 6,
    DAMAGE_SLASHING        = 1 << 7
} damage_flag_t;

typedef uint16_t damage_mask_t;

/* Healing type flags */
typedef enum {
    HEALING_KIND_NONE = 0,
    HEALING_KIND_HP,
    HEALING_KIND_MP,
} healing_kind_t;

typedef uint16_t damage_mask_t;

/***************************************************
 * public variables
 ***************************************************/
extern const vector_t directions[];
extern const dice_roll_t dice[];

/***************************************************
 * function prototypes
 ***************************************************/

void game_init(void);

uint8_t game_roll_dice(dice_kind_t dice);

direction_t game_get_dir_or_cancel_b( void );

#endif // GAME_H