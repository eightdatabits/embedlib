/**
 * @file   emb_assert.h
 * @brief  This file contains the assert defines for all AVR C code.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2017-09-30
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef EMB_ASSERT_H
#define EMB_ASSERT_H

#include <stddef.h>

#ifndef EMB_TRAP
#define EMB_TRAP(f,l) while(1)
#endif

#ifndef EMB_ASSERT
#define EMB_ASSERT(c)                    \
    do {                                 \
        if (!(c)) {                      \
            EMB_TRAP(__FILE__,__LINE__); \
        }                                \
    } while(0)
#endif

#ifndef EMB_ASSERT_RETURN
#define EMB_ASSERT_RETURN(c,r)           \
    do {                                 \
        if (!(c)) {                      \
            return (r);                  \
        }                                \
    } while(0)
#endif

#ifndef EMB_ASSERT_RETURNVOID
#define EMB_ASSERT_RETURNVOID(c)         \
    do {                                 \
        if (!(c)) {                      \
            return;                      \
        }                                \
    } while(0)
#endif

#endif /* EMB_ASSERT_H */
