/**
 * @file text.h
 * @author Paul Johnson
 * @brief 
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TEXT_H
#define TEXT_H
#include <stdint.h>
#include "zxnext.h"


 /***************************************************
 * public types
 ***************************************************/

typedef struct 
{
    uint8_t                 x;
    uint8_t                 y;
    uint8_t                 w;
    uint8_t                 h;
    uint8_t                 c_x;
    uint8_t                 c_y;
    zxnext_tile_t           tile;
} text_window_t;

/***************************************************
 * public function prototypes
 ***************************************************/

/**
 * @brief clears the window
 * 
 * Sets cursor to 0,0
 * 
 * @param win_p 
 */
void text_cls(text_window_t *win_p);

/**
 * @brief Prints char to the specified window
 * 
 * Increments cursor position
 * Handles newline and scrolling
 * 
 * @param win_p 
 * @param c 
 */
void text_putc(text_window_t *win_p, char c);

void text_print_string(text_window_t *win_p, const char text[]);

 void text_printf(text_window_t *win_p, const char *text, ...);

void text_print_uint8(text_window_t *win_p, uint8_t ui);
void text_print_int8(text_window_t *win_p, int8_t i);
void text_print_uint16(text_window_t *win_p, uint16_t ui);
void text_print_int16(text_window_t *win_p, int16_t i);
void text_print_uint32(text_window_t *win_p, uint32_t ul);


#endif // TEXT_H