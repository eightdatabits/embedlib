/**
 * @file      ipin.h
 * @brief     This file contains the common pin driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_IPIN_H
#define JUNK_IPIN_H

#include <stdbool.h>

namespace junk {
namespace hal {

class IPin {
public:
    enum class Direction
    {
        IN  = 0U,
        OUT = 1U
    };

    virtual void setDirection( const Direction dir ) = 0;
    virtual bool read() const = 0;
    virtual void set(bool asserted) = 0;
    virtual void assert() = 0;
    virtual void deassert() = 0;
    virtual void toggle() = 0;
};

} // namespace hal
} // namespace junk

#endif /* JUNK_IPIN_H */
