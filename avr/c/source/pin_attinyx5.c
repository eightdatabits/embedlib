/**
 * @file   pin_attinyx5.c
 * @brief  This file contains pin driver definition for the ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stdbool.h>
#include <stddef.h>
#include <avr/io.h>

#include "embedlib/pin_attinyx5.h"


/* API Function Definitions ==================================================================== */

/**
 * @brief Set the pin's pull up or pull down setting.
 */
bool pin_set_pupd( const pin_t * const pin, const pin_pupd_t pupd )
{
    bool retval = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            if( pupd == PIN_PUPD_NONE )
            {
                PORTB &= ~(1<<(pin->num));
                retval = true;
            }
            else if( pupd == PIN_PUPD_PULLUP )
            {
                PORTB |= (1<<(pin->num));
                retval = true;
            }
            else
            {
                /* Unknown or invalid pupd, default to an error */
            }

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return retval;
}

/**
 * @brief Set the direction of the pin (input/output).
 *
 * @param[in]  pin
 *             The pin to modify.
 * @param[in]  dir
 *             The direction to set.
 */
void pin_set_direction( const pin_t * const pin, const pin_direction_t dir )
{
    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            if( mode == PIN_DIRECTION_INPUT )
            {
                DDRB &= ~(1<<(pin->num));
                retval = true;
            }
            else if( mode == PIN_DIRECTION_OUTPUT )
            {
                DDRB |= (1<<(pin->num));
                retval = true;
            }
            else
            {
                /* Unknown mode, do nothing */
            }

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }
}

/**
 * @brief Read the value at the pin (whether input or output).
 */
bool pin_read( const pin_t * const pin )
{
    bool is_asserted = false;

    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            *is_asserted = (PINB & (1<<(pin->num)));
            retval = true;

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }

    return is_asserted;
}

/**
 * @brief Assert the pin (output only).
 */
void pin_assert( const pin_t * const pin )
{
    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PORTB = pin->is_asserted_low ? (PORTB & ~(1<<(pin->num))) : (PORTB | (1<<(pin->num)));

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }
}

/**
 * @brief Deassert the pin (output only).
 */
void pin_deassert( const pin_t * const pin )
{
    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PORTB = pin->is_asserted_low ? (PORTB | (1<<(pin->num))) : (PORTB & ~(1<<(pin->num)));

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }
}

/**
 * @brief Toggle the value of the pin (output only).
 */
void pin_toggle( const pin_t * const pin )
{
    if( pin != NULL )
    {
        switch( pin->bank )
        {
        case PIN_BANK_A:
            break;

        case PIN_BANK_B:
            PINB |= (1<<(pin->num));

            break;

        case PIN_BANK_C: /* Intentional fall-through */
        case PIN_BANK_D: /* Intentional fall-through */
        case PIN_BANK_E: /* Intentional fall-through */
        case PIN_BANK_F: /* Intentional fall-through */
        case PIN_BANK_G: /* Intentional fall-through */
        case PIN_BANK_H: /* Intentional fall-through */
        default:
            break;
        }
    }
}
