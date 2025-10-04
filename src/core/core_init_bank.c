/**
 * @file init_bank.c
 * @author Paul  Johnson
 * @brief Game INIT_BANK
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "core_init_bank.h"

#include <arch/zxn.h>   /* ZXN_READ_MMU6 and ZXN_WRITE_MMU6*/

#include "zxnext.h"

#include "core/PAGE36/core_init.h"



/***************************************************
 * private defines
 ***************************************************/

/***************************************************
 * private types
 * ***************************************************/

/***************************************************
 * private variables
 * ***************************************************/


/***************************************************
 * private function prototypes
 ***************************************************/

/***************************************************
 * functions
 ***************************************************/


void core_init_bank(void)
{
    uint8_t mmu_6_current_bank;
    uint8_t mmu_7_current_bank;

    mmu_6_current_bank = ZXN_READ_MMU6();     /* Remember current bank*/
    ZXN_WRITE_MMU6(PAGE_INIT);          /* Page init code into 8k MMU slot 6 */

    mmu_7_current_bank = ZXN_READ_MMU7();     /* Remember current bank*/
    ZXN_WRITE_MMU7(PAGE_PALETTE);              /* Page init code into 8k MMU slot 6 */

    core_init();

    ZXN_WRITE_MMU6(mmu_6_current_bank);       /* restore previous bank */  
    ZXN_WRITE_MMU7(mmu_7_current_bank);       /* restore previous bank */  
}