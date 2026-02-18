/**
 * @file memory_map.h
 * @author Paul Johnson
 * @brief Memory page definitions
 */

#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

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
 * slot 0 (0x000)     Fixed global memory_map state (by default would contain the ROM)
 * slot 1 (0x2000)    Fixed global memory_map state (by default would contain the ROM) 
 * slot 2 (0x4000)    Fixed tilemap and tilesets (bank 5)
 * slot 3 (0x6000)    Fixed tilemap and tilesets (bank 5)
 * slot 4 (0x8000)    Fixed non banking core memory_map code (bank 2)
 * slot 5 (0xa000)    Fixed non banking core memory_map code (bank 2)
 * slot 6 (0xc000)    Banked memory_map code and data (bank 0) 
 * slot 7 (0xe000)    Banked memory_map code and data (bank 0)
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
  *     odd page numbers have a default ORG of 0xe000 e.g. page 31, 33
  */

#define PAGE_GLOBAL_STATE     28 
#define PAGE_GLOBAL_STATE_2   29 
#define PAGE_MONSTER_SYSTEM   30
#define PAGE_ITEM_SYSTEM      32
#define PAGE_DUNGEON_GEN      34
#define PAGE_INIT             36
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
#define PAGE_FEATURE_SYSTEM   72
#define PAGE_DOOR_SYSTEM      74
#define PAGE_TRANSITION_SYSTEM      74

/*
 * Bank switching macros. Do not use from within a bank that is being switched out. 
 */
#define BANK_SAVE_MMU6()     uint8_t __old_bank = ZXN_READ_MMU6()
#define BANK_RESTORE_MMU6()  ZXN_WRITE_MMU6(__old_bank)
#define BANK_SWITCH_MMU6(bank)  ZXN_WRITE_MMU6(bank)

#define CALL_BANKED_VOID0(bank, fn)          \
do {                                        \
    BANK_SAVE_MMU6();                       \
    BANK_SWITCH_MMU6(bank);                 \
    fn();                                   \
    BANK_RESTORE_MMU6();                    \
} while (0)

#define CALL_BANKED_VOID1(bank, fn, a)       \
do {                                        \
    BANK_SAVE_MMU6();                       \
    BANK_SWITCH_MMU6(bank);                 \
    fn(a);                                  \
    BANK_RESTORE_MMU6();                    \
} while (0)

#define CALL_BANKED_VOID2(bank, fn, a, b)    \
do {                                        \
    BANK_SAVE_MMU6();                       \
    BANK_SWITCH_MMU6(bank);                 \
    fn(a, b);                               \
    BANK_RESTORE_MMU6();                    \
} while (0)

#define CALL_BANKED_RET0(bank, result, fn)   \
do {                                        \
    BANK_SAVE_MMU6();                       \
    BANK_SWITCH_MMU6(bank);                 \
    (result) = fn();                        \
    BANK_RESTORE_MMU6();                    \
} while (0)

#define CALL_BANKED_RET1(bank, result, fn, a)\
do {                                        \
    BANK_SAVE_MMU6();                       \
    BANK_SWITCH_MMU6(bank);                 \
    (result) = fn(a);                       \
    BANK_RESTORE_MMU6();                    \
} while (0)

#define CALL_BANKED_RET2(bank, result, fn, a, b) \
do {                                            \
    BANK_SAVE_MMU6();                           \
    BANK_SWITCH_MMU6(bank);                     \
    (result) = fn(a, b);                        \
    BANK_RESTORE_MMU6();                        \
} while (0)


/***************************************************
 * public variables
 ***************************************************/

/***************************************************
 * function prototypes
 ***************************************************/

#endif // MEMORY_MAP_H