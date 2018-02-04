/**
 * @file      itimer.h
 * @brief     This file contains the common hardware timer driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_ITIMER_H
#define JUNK_ITIMER_H

#include <stdbool.h>

namespace junk {

class ITimer {
public:
    virtual bool start() = 0;
    virtual bool pause() = 0;
    virtual bool reset() = 0;
};

} // namespace junk

#endif /* JUNK_ITIMER_H */
