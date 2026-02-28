/**
 * @file ui_info.c
 * @author Paul Johnson
 * @brief Context-sensitive info bar (info_win) hint text
 *
 * @copyright Copyright (c) 2025
 */

#include "game/ui_info.h"

#include "game/global_state.h"
#include "core/text.h"

/***************************************************
 * private variables
 ***************************************************/

static const char * const s_hints[] = {
    /* UI_CONTEXT_NORMAL    */ "[%PYarr%PW]Move [%PYg%PW]Get [%PYi%PW]Inv [%PYo/c%PW]Door[%PYa%PW]Atk",
    /* UI_CONTEXT_DIRECTION */ "[%PYarrows%PW]Direction  [%PYspace%PW]Cancel",
    /* UI_CONTEXT_TARGETING */ "[%PYarrows%PW]Cursor [%PYt%PW]Attack [%PYspace%PW]Cancel",
    /* UI_CONTEXT_LOOK      */ "[%PYarrows%PW]Cursor [%PYl%PW]Look [%PYspace%PW]Cancel",
};

/***************************************************
 * public functions
 ***************************************************/

void ui_info_set_context(ui_context_t ctx)
{
    text_cls(&g.info_win);
    text_printf(&g.info_win, s_hints[ctx]);
}

void ui_info_set_inventory_context(char max_char)
{
    text_cls(&g.info_win);
    text_printf(&g.info_win, "[%PYa-%c%PW]Select  [%PYspace%PW]Cancel", max_char);
}
