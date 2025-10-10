/**
 * @file util.h
 * @author Paul Johnson
 * @brief 
 * @version 0.1
 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UTIL_H
#define UTIL_H

/***************************************************
 * function prototypes
 ***************************************************/

void util_assert_f(const char *message, const char *file, unsigned line);

void util_abort_f(const char *message, const char *file, unsigned line);

/***************************************************
 * macros
 ***************************************************/
/* If DEBUG defined, enable assert */
#ifdef NDEBUG
    #define util_assert(_Expression) ((void)0)
#else /* !defined (NDEBUG) */
    #define util_assert(_Expression) \
        do { \
            if (!(_Expression)) \
                util_assert_f(#_Expression, __FILE__, __LINE__); \
        } while(0)
#endif /* !defined (NDEBUG) */

#define util_abort(message) util_abort_f(message, __FILE__,__LINE__);

#endif // UTIL_H