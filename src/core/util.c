/**
 * @file util.c
 * @author Paul  Johnson
 * @brief 
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "util.h"

#include <stdlib.h>
#include <stdint.h>

#include "game/global_state.h"
#include "core/text.h"
#include "zxnext.h"

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
void util_assert_f(const char *message, const char *file, unsigned line)
{
    text_printf(&g.msg_win, "ASSERT FAIL: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);
}

void util_info_f(const char *message)
{
    text_printf(&g.msg_win, "INFO: %s\n", message);
}

void util_abort_f(const char *message, const char *file, unsigned line)
{
    text_printf(&g.msg_win, "ABORT: %s FILE:%s LINE:%l", message, file, (unsigned long)line);
    while(1);
}