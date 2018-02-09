/**
 * @file   junk_assert.h
 * @brief  This file contains the assert defines for all AVR C code.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2017-09-30
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_ASSERT_H
#define JUNK_ASSERT_H

#include <stddef.h>

#ifndef JUNK_TRAP
#define JUNK_TRAP(f,l) while(1)
#endif

#ifndef JUNK_ASSERT
#define JUNK_ASSERT(c)                    \
    do {                                 \
        if (!(c)) {                      \
            JUNK_TRAP(__FILE__,__LINE__); \
        }                                \
    } while(0)
#endif

#ifndef JUNK_ASSERT_RETURN
#define JUNK_ASSERT_RETURN(c,r)           \
    do {                                 \
        if (!(c)) {                      \
            return (r);                  \
        }                                \
    } while(0)
#endif

#ifndef JUNK_ASSERT_RETURNVOID
#define JUNK_ASSERT_RETURNVOID(c)         \
    do {                                 \
        if (!(c)) {                      \
            return;                      \
        }                                \
    } while(0)
#endif

#endif /* JUNK_ASSERT_H */
