/**
 * @file   spi_attinyx5.c
 * @brief  This file contains the SPI driver implementation for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "embedlib/spi_attinyx5.h"

/* API Function Definitions ==================================================================== */

bool spi_init( spi_t * const spi )
{
    bool success = false;

    if( spi != NULL )
    {
        if( (spi->cs != NULL) && (spi->mosi != NULL) && (spi->miso != NULL) && (spi->sclk != NULL) )
        {
            /* Initialize CS pin */
            pin_set_direction( spi->cs ), PIN_DIRECTION_OUTPUT );
            pin_deassert( spi->cs );

            /* Initialize MOSI pin */
            pin_set_direction( spi->mosi ), PIN_DIRECTION_OUTPUT );
            pin_deassert( spi->mosi );

            /* Initialize MISO pin */
            pin_set_direction( spi->miso ), PIN_DIRECTION_INPUT );

            /* Initialize SCLK pin */
            pin_set_direction( spi->sclk ), PIN_DIRECTION_OUTPUT );
            pin_deassert( spi->sclk );

            /* Initialize USI registers */
            /* Three-wire mode, USI software clock */
            USICR = (1<<USIWM0) | (1<<USICLK);

            success = true;
        }
    }

    return success;
}

bool spi_enable_cs( spi_t * const spi )
{
    bool success = false;

    if( spi != NULL )
    {
        /* Assert CS pin */
        pin_assert( spi->cs );
    }

    return success;
}

bool spi_disable_cs( spi_t * const spi )
{
    bool success = false;

    if( spi != NULL )
    {
        /* Deassert CS pin */
        pin_deassert( spi->cs );
    }

    return success;
}

bool spi_write_read( spi_t * const spi,
                     uint8_t * const read_bytes,
                     const uint8_t * const write_bytes,
                     const uint8_t num_bytes )
{
    bool success = false;
    uint8_t bytes_written = 0;

    if( (spi != NULL) &&
        (read_bytes != NULL) &&
        (write_bytes != NULL) )
    {
        while( bytes_written < num_bytes ) {
            /* Write byte to USI register */
            USIDR = write_bytes[bytes_written];

            /* Clear 4-bit counter and overflow flag */
            USISR = (1<<USIOIF);

            while( (USISR & (1<<USIOIF)) == 0 )
            {
                /* Strobe clock and shift next bit out */
                USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);
            }

            read_bytes[bytes_written] = USIDR;

            bytes_written++;
        }

        success = true;
    }

    return success;
}

bool spi_write( spi_t * const spi, const uint8_t * const write_bytes, const uint8_t num_bytes )
{
    uint8_t dummy_reads[num_bytes];

    return spi_write_read( spi, &dummy_reads[0], write_bytes, num_bytes );
}

bool spi_read( spi_t * const spi, uint8_t * const read_bytes, const uint8_t num_bytes )
{
    uint8_t dummy_writes[num_bytes] = {0};

    return spi_write_read( spi, read_bytes, &dummy_writes[0], num_bytes );
}