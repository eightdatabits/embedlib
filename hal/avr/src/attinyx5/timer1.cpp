/**
 * @file   timer1.cpp
 * @brief  This file contains the timer1 driver implementation for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-13
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "junk/hal/attinyx5/timer1.h"

namespace junk {
namespace hal {

Timer1::Timer1( Prescaler pre, bool reset_on_match )
    : m_prescaler(pre)
{
    /* Pause timer and set reset on match option */
    TCCR1 = reset_on_match ? TCCR1 | (1<<CTC1) : TCCR1 & ~(1<<CTC1);

    /* Reset prescaler */
    GTCCR = (1<<PSR1);

    /* Reset timer value */
    TCNT1 = 0x00U;

    /* Reset compare values */
    OCR1A = 0x00U;
    OCR1B = 0x00U;
    OCR1C = 0x00U;
}

Timer1::~Timer1()
{
    (void)disableIrq();
    (void)reset();
}

bool Timer1::start()
{
    bool success = false;

    // Ensure timer isn't already running
    if (!isRunning()) {
        /* Set prescaler configuration (which starts timer) */
        TCCR1 |= m_prescaler;
        success = true;
    }

    return success;
}

bool Timer1::pause()
{
    /* Clear prescaler configuration (which pauses timer) */
    TCCR1 &= ~( (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10) );

    return true;
}

bool Timer1::reset()
{
    bool success = false;

    success = pause();
    success = setCounter(0x00U) && success;

    return success;
}

bool Timer1::isRunning() const
{
    return ((TCCR1 & 0x0FU) != 0x00U);
}

bool Timer1::setPrescaler( Prescaler pre )
{
    bool success = false;

    if( !isRunning() )
    {
        // Set new prescaler value
        m_prescaler = pre;
        success = true;
    }

    return success;
}

bool Timer1::setCounter( const uint8_t value )
{
    bool success = false;

    if( !isRunning() )
    {
        /* Reset prescaler */
        GTCCR = (1<<PSR1);
        /* Set new timer value */
        TCNT1 = value;
        success = true;
    }

    return success;
}

uint8_t Timer1::getCounter() const
{
    /* Get current timer value */
    return TCNT1;
}

bool Timer1::enableIrq()
{
    bool success = false;

    if( !isRunning() )
    {
        /* Enable OCIE1A interrupt */
        TIMSK |= (1<<OCIE1A);
        success = true;
    }

    return success;
}

bool Timer1::disableIrq()
{
    bool success = false;

    if( !isRunning() )
    {
        /* Disable OCIE1A interrupt */
        TIMSK &= ~(1<<OCIE1A);
        success = true;
    }

    return success;
}

bool Timer1::setCompare( const uint8_t value )
{
    bool success = false;

    if( !isRunning() )
    {
        /* Set OCR1A as the normal match register  */
        OCR1A = value;
        /* Set OCR1C as the reset on match register */
        OCR1C = value;
        success = true;
    }

    return success;
}

uint8_t Timer1::getCompare() const
{
    /* Get OCR1A as the normal match register  */
    return OCR1A;
}

} // namespace hal
} // namespace junk
