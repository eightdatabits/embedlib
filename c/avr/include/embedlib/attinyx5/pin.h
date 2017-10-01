/**
 * @file   pin_attinyx5.h
 * @brief  This file contains the pin driver definition for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef PIN_ATTINYx5_H
#define PIN_ATTINYx5_H

#ifndef PIN_H
#error "Include pin.h instead of this file."
#endif

#include <stdbool.h>

typedef enum pin_bank_e
{
    PIN_BANK_A = 0U,
    PIN_BANK_B = 1U,
    PIN_BANK_C = 2U,
    PIN_BANK_D = 3U,
    PIN_BANK_E = 4U,
    PIN_BANK_F = 5U,
    PIN_BANK_G = 6U,
    PIN_BANK_H = 7U
} pin_bank_t;

typedef enum pin_num_e
{
    PIN_NUM_0 = 0U,
    PIN_NUM_1 = 1U,
    PIN_NUM_2 = 2U,
    PIN_NUM_3 = 3U,
    PIN_NUM_4 = 4U,
    PIN_NUM_5 = 5U,
    PIN_NUM_6 = 6U,
    PIN_NUM_7 = 7U
} pin_num_t;

typedef enum pin_pupd_e
{
    PIN_PUPD_NONE     = 0U,
    PIN_PUPD_PULLDOWN = 1U,
    PIN_PUPD_PULLUP   = 2U
} pin_pupd_t;

typedef struct pin_s
{
    pin_bank_t bank;
    pin_num_t  num;
    bool is_asserted_low;
} pin_t;

bool pin_set_pupd( const pin_t * const pin,
                   const pin_pupd_t pupd );

#endif /* PIN_ATTINYx5_H */
