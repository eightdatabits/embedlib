/**
 * @file   timer_attinyx5.c
 * @brief  This file contains the common timer driver implementation for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-13
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

#include "embedlib/timer_attinyx5.h"


bool timer_init( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Pause timer and set reset on match option */
            TCCR1 = timer->reset_on_match ? TCCR1 | (1<<CTC1) : TCCR1 & ~(1<<CTC1);

            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Reset timer value */
            TCNT1 = 0x00U;

            /* Reset compare values */
            OCR1A = 0x00U;
            OCR1B = 0x00U;
            OCR1C = 0x00U;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_enable_int( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Enable OCIE1A interrupt */
            TIMSK |= (1<<OCIE1A);

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_disable_int( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Disable OCIE1A interrupt */
            TIMSK &= ~(1<<OCIE1A);

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_start( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Set prescaler configuration (which starts timer) */
            TCCR1 |= timer->prescaler;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_pause( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Clear prescaler configuration (which pauses timer) */
            TCCR1 &= ~( (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10) );

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_reset( const timer_t * const timer )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Clear prescaler configuration (which pauses timer) */
            TCCR1 &= ~( (1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10) );

            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Reset timer value */
            TCNT1 = 0x00U;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_set_compare( const timer_t * const timer, const uint8_t value )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Set OCR1A as the normal match register  */
            OCR1A = value;

            /* Set OCR1C as the reset on match register */
            OCR1C = value;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_get_compare( const timer_t * const timer, uint8_t * const value )
{
    bool success = false;

    if( (timer != NULL) &&
        (value != NULL) )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Get OCR1A as the normal match register  */
            *value = OCR1A;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_set( const timer_t * const timer, const uint8_t value )
{
    bool success = false;

    if( timer != NULL )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Reset prescaler */
            GTCCR = (1<<PSR1);

            /* Set new timer value */
            TCNT1 = value;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}

bool timer_get( const timer_t * const timer, uint8_t * const value )
{
    bool success = false;

    if( (timer != NULL) &&
        (value != NULL) )
    {
        switch( timer->number )
        {
        case TIMER_NUM_0:
            /* Not implemented yet */

            break;

        case TIMER_NUM_1:
            /* Timer/counter1 */
            /* Get current timer value */
            *value = TCNT1;

            success = true;

            break;

        case TIMER_NUM_2: /* Intentional fallthrough */
        case TIMER_NUM_3: /* Intentional fallthrough */
        case TIMER_NUM_4: /* Intentional fallthrough */
        case TIMER_NUM_5: /* Intentional fallthrough */
        case TIMER_NUM_6: /* Intentional fallthrough */
        case TIMER_NUM_7: /* Intentional fallthrough */
        default:
            /* Unknown timer */
            break;
        }
    }

    return success;
}