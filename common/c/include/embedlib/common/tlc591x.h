/**
 * @file      tlc591x.h
 * @brief     This file contains the TLC591x driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef TLC591x_H
#define TLC591x_H

#include <stdint.h>
#include "embedlib/common/pin.h"
#include "embedlib/common/spi.h"

typedef struct tlc591x_s
{
    spi_t* spi;
    pin_t* le;
    pin_t* n_oe;
} tlc591x_t;

bool tlc591x_init( tlc591x_t * const tlc );
bool tlc591x_enable_output( tlc591x_t * const tlc );
bool tlc591x_disable_output( tlc591x_t * const tlc );
bool tlc591x_write_values( tlc591x_t * const tlc, const uint8_t values );

#endif // TLC591x_H
