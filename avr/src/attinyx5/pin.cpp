/**
 * @file      pin.cpp
 * @brief     This file contains the pin driver definition for the ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stdbool.h>
#include <stddef.h>
#include <avr/io.h>

#include "junk/common/emb_assert.h"
#include "junk/attinyx5/pin.h"

namespace junk {

/* API Function Definitions ==================================================================== */

/**
 * @brief Construct a Pin driver.
 *
 * @note ATTinyx5 chips only have Port B pins, so no port option is available.
 *
 * @param[in]  num
 *             The pin number to assign.
 * @param[in]  asserted_high
 *             True if the pin is asserted high.
 * @return [description]
 */
Pin::Pin( const PinNum num, const bool asserted_high )
    : m_num(num), m_asserted_high(asserted_high)
{
    JUNK_ASSERT(m_num < 8);
}

/**
 * @brief Set the pin's pull up or pull down setting.
 *
 * @param[in]  pupd
 *             Whether to turn on the pull up, pull down, or neither.
 * @return True for success, false for failure.
 */
void Pin::setPuPd( const PuPd pupd )
{
    if( pupd == PUPD_NONE )
    {
        PORTB &= ~(1<<(m_num));
    }
    else if( pupd == PUPD_PULLUP )
    {
        PORTB |= (1<<(m_num));
    }
    else
    {
        /* Unknown or invalid pupd, don't do anything */
    }
}

/**
 * @brief Set the direction of the pin (input/output).
 *
 * @param[in]  pin
 *             The pin to modify.
 * @param[in]  dir
 *             The direction to set.
 * @return True for success, false for failure.
 */
void Pin::setDirection( const Direction dir )
{
    if( dir == DIRECTION_IN )
    {
        DDRB &= ~(1<<(m_num));
    }
    else if( dir == DIRECTION_OUT )
    {
        DDRB |= (1<<(m_num));
    }
    else
    {
        /* Unknown direction, do nothing */
    }
}

/**
 * @brief Read the value at the pin (whether input or output).
 */
bool Pin::read() const
{
    return (m_asserted_high == (bool)(PINB & (1<<(m_num))));
}

/**
 * @brief Assert the pin (output only).
 */
void Pin::assert()
{
    PORTB = m_asserted_high ? (PORTB | (1<<(m_num))) : (PORTB & ~(1<<(m_num)));
}

/**
 * @brief Deassert the pin (output only).
 */
void Pin::deassert()
{
    PORTB = m_asserted_high ? (PORTB & ~(1<<(m_num))) : (PORTB | (1<<(m_num)));
}

/**
 * @brief Toggle the value of the pin (output only).
 */
void Pin::toggle()
{
    PINB |= (1<<(m_num));
}

} // namespace junk
