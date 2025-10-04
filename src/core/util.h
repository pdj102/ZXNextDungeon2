/**
 * @file util.h
 * @author Paul Johnson
 * @brief Utility functions for the game engine.
 
 */

#ifndef UTIL_H
#define UTIL_H

/***************************************************
 * public defines
 ***************************************************/

/***************************************************
 * public types
 ***************************************************/

/***************************************************
 * public variables
 ***************************************************/


/***************************************************
 * function prototypes
 ***************************************************/
void util_assert_f(const char *message, const char *file, unsigned line);

void util_info_f(const char *message);

void util_abort_f(const char *message, const char *file, unsigned line);

/***************************************************
 * macros
 ***************************************************/
/* If DEBUG defined, enable assert */
#ifdef NDEBUG
    #define util_assert(_Expression) ((void)0)
    #define util_info(message) ((void)0)
#else /* !defined (NDEBUG) */
    #define util_assert(_Expression) \
        do { \
            if (!(_Expression)) \
                util_assert_f(#_Expression, __FILE__, __LINE__); \
        } while(0)
    #define util_info(message) \
        do { \
            util_info_f((message)); \
        } while (0)

#endif /* !defined (NDEBUG) */


#define util_abort(message) \
    do { \
        util_abort_f((message), __FILE__, __LINE__); \
    } while (0)


#endif // UTIL_H