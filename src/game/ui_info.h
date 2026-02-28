/**
 * @file ui_info.h
 * @author Paul Johnson
 * @brief Context-sensitive info bar (info_win) hint text
 *
 * @copyright Copyright (c) 2025
 */

#ifndef UI_INFO_H
#define UI_INFO_H

/***************************************************
 * public types
 ***************************************************/

typedef enum {
    UI_CONTEXT_NORMAL,      /* Movement + all main action keys  */
    UI_CONTEXT_DIRECTION,   /* Awaiting a direction keypress    */
    UI_CONTEXT_TARGETING,   /* Targeting cursor (ranged attack) */
    UI_CONTEXT_LOOK,        /* Look-mode cursor                 */
} ui_context_t;

/***************************************************
 * public function prototypes
 ***************************************************/

void ui_info_set_context(ui_context_t ctx);
void ui_info_set_inventory_context(char max_char);

#endif /* UI_INFO_H */
