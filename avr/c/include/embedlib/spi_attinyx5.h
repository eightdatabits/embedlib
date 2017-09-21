/**
 * @file      spi_attinyx5.h
 * @brief     This file contains the SPI driver declaration for the AVR ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef SPI_ATTINYx5_H
#define SPI_ATTINYx5_H

#include <stdbool.h>

#include "embedlib/common/spi.h"
#include "embedlib/pin_attinyx5.h"

typedef enum spi_baud_e
{
    SPI_BAUD_100K = 0U,
    SPI_BAUD_200K = 1U,
    SPI_BAUD_500K = 2U,
    SPI_BAUD_1M   = 3U
} spi_baud_t;

typedef enum spi_mode_e
{
    SPI_MODE_0 = 0U,
    SPI_MODE_1 = 1U,
    SPI_MODE_2 = 2U,
    SPI_MODE_3 = 3U
} spi_mode_t;

typedef struct spi_s
{
    spi_baud_t baudrate;
    spi_mode_t mode;
    pin_t* cs;
    pin_t* mosi;
    pin_t* miso;
    pin_t* sclk;
} spi_t;

bool spi_init( spi_t * const spi );

#endif /* SPI_ATTINYx5_H */
