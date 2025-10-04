/**
 * @file zxnext.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "zxnext.h"

#include <arch/zxn.h>

#define REG_ULA_CONTROL 0x68 
#define RUC_DISABLE_ULA_OUTPUT 0b10000000 /* bit 7 = 1 to disable ULA output */
#define RTM_28MHZ 0b00000011 /* bits 1-0 = 11 for 28MHz */

void zxnext_init(void) {
    /* set CPU speed 28MHz */
    ZXN_WRITE_REG(REG_TURBO_MODE, RTM_28MHZ);

    /* disable RAM contention */
    ZXN_WRITE_REG(REG_PERIPHERAL_3, (ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION));

    /* Disable the ZXnext ULA screen */
    // ZXN_WRITE_REG(REG_ULA_CONTROL, (ZXN_READ_REG(REG_ULA_CONTROL) | RUC_DISABLE_ULA_OUTPUT));
}
