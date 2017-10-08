/**
 * @file   spi.cpp
 * @brief  This file contains the SPI driver implementation for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

#include "embedlib/attinyx5/spi.h"

namespace emb {

/* API Function Definitions ==================================================================== */

Spi::Spi( Pin& cs, Pin& mosi, Pin& miso, Pin& sclk )
    : m_baudrate(BAUD_100K), m_mode(MODE_0), m_cs(cs), m_mosi(mosi), m_miso(miso), m_sclk(sclk)
{
    /* Initialize CS pin */
    m_cs.setDirection( IPin::DIRECTION_OUT );
    m_cs.deassert();

    /* Initialize MOSI pin */
    m_mosi.setDirection( IPin::DIRECTION_OUT );
    m_mosi.deassert();

    /* Initialize MISO pin */
    m_miso.setDirection( IPin::DIRECTION_IN );

    /* Initialize SCLK pin */
    m_sclk.setDirection( IPin::DIRECTION_OUT );
    m_sclk.deassert();

    /* Initialize USI registers */
    /* Three-wire mode, USI software clock */
    USICR = (1<<USIWM0) | (1<<USICLK);
}

/**
 * @brief Assert the CS pin.
 *
 * @note Doesn't check for CS already asserted.
 *
 * @return Always true.
 */
bool Spi::enableCs()
{
    /* Assert CS pin */
    m_cs.assert();

    return true;
}

/**
 * @brief Deassert CS pin.
 *
 * @note Doesn't check for CS already deasserted.
 *
 * @return Always true.
 */
bool Spi::disableCs()
{
    /* Deassert CS pin */
    m_cs.deassert();

    return true;
}

/**
 * @brief Write to the SPI bus and return the received bytes.
 *
 * @warning Baud rate is not used here, currently the bits are just written out as fast as possible.
 *
 * @note Both `read_bytes` and `write_bytes` may not be NULL.
 *
 * @param[out] read_bytes
 *             The bytes received while writing. May be NULL only if `write_bytes` is not NULL.
 *             Causes received bytes to be ignored.
 * @param[in]  write_bytes
 *             The bytes to be written to the bus. May be NULL only if `read_bytes` is not NULL.
 *             Causes `0` to be written and received bytes to be stored in `read_bytes`.
 * @param[in]  num_bytes
 *             The number of bytes in the write_bytes buffer.
 * @return The number of bytes written/received. If zero, either `num_bytes` was zero or an error
 *         occurred.
 */
size_t Spi::writeRead( uint8_t * const read_bytes,
                       const uint8_t * const write_bytes,
                       const size_t num_bytes )
{
    size_t bytes_written = 0;

    if( (read_bytes == NULL) && (write_bytes == NULL) ) {
        /* Both read_bytes and write_bytes cannot be NULL */
        return 0;
    }

    while( bytes_written < num_bytes ) {
        if( write_bytes != NULL ) {
            /* Write byte to USI register */
            USIDR = write_bytes[bytes_written];
        } else {
            USIDR = 0x00;
        }

        /* Clear 4-bit counter and overflow flag */
        USISR = (1<<USIOIF);

        while( (USISR & (1<<USIOIF)) == 0 )
        {
            /* Strobe clock and shift next bit out */
            USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC);
        }

        if( read_bytes != NULL )
        {
            read_bytes[bytes_written] = USIDR;
        }

        bytes_written++;
    }

    return bytes_written;
}

size_t Spi::write( const uint8_t * const write_bytes, const size_t num_bytes )
{
    return writeRead( NULL, write_bytes, num_bytes );
}

size_t Spi::read( uint8_t * const read_bytes, const size_t num_bytes )
{
    return writeRead( read_bytes, NULL, num_bytes );
}

} // namespace emb
