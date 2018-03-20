/**
 * @file      pin.h
 * @brief     This file contains the pin driver definition for the AVR ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_ATTINYx5_PIN_H
#define JUNK_ATTINYx5_PIN_H

#include <stdbool.h>

#include "junk/hal/ipin.h"

namespace junk {
namespace hal {

class Pin : public IPin {
public:
    typedef uint8_t PinNum;

    /**
     * @brief Pull-up/Pull-down options.
     *
     * The ATTinyx5 family only provides for pull-up or no pull options.
     */
    enum class PuPd
    {
        NONE     = 0U, ///< No pull-up on the pin.
        PULLUP   = 1U  ///< Set a pull-up on the pin.
    };

    /* Note: There is only one pin bank in the ATTinyx5 family: bank B */
    Pin(const PinNum num, const bool asserted_high = true);
    virtual ~Pin() = default;

    void setPuPd( const PuPd pupd );
    void setDirection( const Direction dir ) override final;
    bool read() const override final;
    void set(bool asserted) override final;
    void assert() override final;
    void deassert() override final;
    void toggle() override final;

private:
    PinNum m_num;
    bool m_asserted_high;
};

} // namespace hal
} // namespace junk

#endif /* JUNK_ATTINYx5_PIN_H */
