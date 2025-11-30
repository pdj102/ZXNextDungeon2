/**
 * @file text.c
 * @author Paul Johnson
 * @brief 
 * 
 */

 #include "core/text.h"

 #include <stddef.h>   /* NULL */
 #include <stdint.h>    /* uint8_t, uint16_t etc */
 #include <string.h>    /* strlen */
 #include <stdlib.h>    /* itoa, utoa, ultoa */
 #include <stdarg.h>    /* variadic functions */

 #include "zxnext.h"
 #include "util.h"


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

void text_scroll_up( text_window_t *win_p );

/***************************************************
 * functions
 ***************************************************/

 void text_cls(text_window_t *win_p)
 {
    util_assert(win_p != NULL);

    uint8_t x2 = win_p->x + win_p->w;
    uint8_t y2 = win_p->y + win_p->h;

    win_p->tile.tile_id = ' '; /* clear using space character */

    for (uint8_t y = win_p->y; y < y2; y++) {
        for (uint8_t x = win_p->x; x < x2; x++) {
            zxnext_tilemap_set(x, y, &win_p->tile);
        }
    }
    win_p->c_x = 0;
    win_p->c_y = 0;
 }

 void text_putc(text_window_t *win_p, char c)
 {
    util_assert(win_p != NULL);

    if (c == '\n') {
        win_p->c_x = 0;
        win_p->c_y++;
        if (win_p->c_y >= win_p->h) {
            text_scroll_up(win_p);
            win_p->c_y = win_p->h - 1;
        }
        return;
    }

    win_p->tile.tile_id = (uint8_t)c; /* set the character */

    uint8_t x = win_p->x + win_p->c_x;
    uint8_t y = win_p->y + win_p->c_y;

    zxnext_tilemap_set(x, y, &win_p->tile);

    win_p->c_x++;
    if (win_p->c_x >= win_p->w) {
        win_p->c_x = 0;
        win_p->c_y++;
        if (win_p->c_y >= win_p->h) {
            text_scroll_up(win_p);
            win_p->c_y = win_p->h - 1;
        }
    }
 }

 void text_printf(text_window_t *win_p, const char *text, ...)
{
    va_list ptr;
    va_start(ptr, text);

    uint8_t l = strlen(text);

    for (uint8_t i = 0; i < l; i++)
    {
        if (text[i] != '%')
        {
            text_putc(win_p, text[i]);
            continue;
        }

        i++;

        switch(text[i])
        {
            case 'u':   // uint8_t (promoted to int)
            text_print_uint8(win_p, (uint8_t) va_arg(ptr, int) );
            break;

            case 'd':   // int8_t (promoted to int)
            text_print_int8(win_p, (int8_t) va_arg(ptr, int) );
            break;

            case 'U':   // uint16_t (promoted to int)
            text_print_uint16(win_p, (uint16_t) va_arg(ptr, int) );
            break;

            case 'D':   // int16_t (promoted to int)
            text_print_int16(win_p, (int16_t) va_arg(ptr, int) );
            break;

            case 'l':   // uint32_t / unsigned long (lowercase l)
            text_print_uint32(win_p, (uint32_t) va_arg(ptr, unsigned long) );
            break;

            case 'c':   // char (promoted to int)
            text_putc(win_p, (char) va_arg(ptr, int) );
            break;

            case 's':   // string
            text_print_string(win_p, (const char*) va_arg(ptr, const char*) );
            break;        

            case '%':   // a literal % character
            text_putc(win_p, '%');
            break;                                  

            default:
            text_putc(win_p, '?');
        }
    }
    va_end(ptr);
}

void text_print_string(text_window_t *win_p, const char text[])
{
    uint8_t l = strlen(text);

    for (uint8_t i = 0; i < l; i++)
    {
            text_putc(win_p, text[i]);
    }
}

void text_print_uint8(text_window_t *win_p, uint8_t ui)
{
    char s[] = "   ";     // string buffer for converting numbers to strings e.g. 255
    
    utoa(ui, s, 10);
    text_print_string(win_p, s);
}

void text_print_int8(text_window_t *win_p, int8_t i)
{
    char s[] = "    ";     // string buffer for converting numbers to strings e.g. -128
    
    itoa(i, s, 10);
    text_print_string(win_p, s);
}

void text_print_uint16(text_window_t *win_p, uint16_t ui)
{
    char s[] = "65535";     // string buffer for converting numbers to strings
    
    utoa(ui, s, 10);
    text_print_string(win_p, s);
}

void text_print_uint32(text_window_t *win_p, uint32_t ul)
{
    char s[] = "4294967295";

    ultoa(ul, s, 10);
    text_print_string(win_p, s);    
}

void text_print_int16(text_window_t *win_p, int16_t i)
{
    char s[] = "-32768";     // string buffer for converting numbers to strings
    
    itoa(i, s, 10);
    text_print_string(win_p, s);
}



 void text_scroll_up( text_window_t *win_p )
 {
    util_assert(win_p != NULL);

    /* scroll the text window up by one line */
    uint8_t x2 = win_p->x + win_p->w;
    uint8_t y2 = win_p->y + win_p->h;
    for (uint8_t y = win_p->y; y < (y2 - 1); y++) {
        for (uint8_t x = win_p->x; x < x2; x++) {
            zxnext_tilemap_copy(x, y + 1, x, y);
        }
    }
    /* clear the last line */
    win_p->tile.tile_id = ' '; /* space character */
    for (uint8_t x = win_p->x; x < x2; x++) {
        zxnext_tilemap_set(x, y2 - 1, &win_p->tile);
    }
}


    