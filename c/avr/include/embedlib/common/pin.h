/**
 * @file      pin.h
 * @brief     This file contains the common pin driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef PIN_H
#define PIN_H

#include <stdbool.h>

/* Forward declaration of pin driver struct */
struct pin_s;
typedef struct pin_s pin_t;

typedef enum pin_direction_e
{
    PIN_DIRECTION_IN  = 0U,
    PIN_DIRECTION_OUT = 1U
} pin_direction_t;

void pin_set_direction( const pin_t * const pin, const pin_direction_t dir );
bool pin_read( const pin_t * const pin );
void pin_assert( const pin_t * const pin );
void pin_deassert( const pin_t * const pin );
void pin_toggle( const pin_t * const pin );

/* Include processor specific header */
#if defined (__AVR_ATtiny25__)
#include "embedlib/attinyx5/pin.h"
#elif defined (__AVR_ATtiny45__)
#include "embedlib/attinyx5/pin.h"
#elif defined (__AVR_ATtiny85__)
#include "embedlib/attinyx5/pin.h"
#endif

#endif /* PIN_H */
