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

#include "junk/hal/attinyx5/spi.h"

namespace junk {
namespace hal {

/* API Function Definitions ==================================================================== */

/**
 * @brief SPI driver constructor.
 *
 * Constructs an SPI master driver. Sets the mode and optionally the CS pin.
 *
 * @param[in]  mode
 *             The bus mode to use.
 * @param[in]  cs
 *             A pointer to a Pin representing the CS pin. Used by `enableCs()` and `disableCs()`.
 */
Spi::Spi(Mode mode, Pin* cs)
    : m_mode(mode), m_cs(cs)
{
    if (m_cs != nullptr) {
        m_cs->deassert();
        m_cs->setDirection(Pin::Direction::OUT);
    }

    // Initialize SPI pins, these don't need to be persistent
    DDRB |= (1<<(PIN_MOSI));   // MOSI: output
    PORTB &= ~(1<<(PIN_MOSI)); // MOSI: default low
    DDRB |= (1<<(PIN_SCLK));   // SCLK: output
    PORTB &= ~(1<<(PIN_SCLK)); // SCLK: default low
    DDRB &= ~(1<<(PIN_MISO));  // MISO: input

    /* Initialize USI registers */
    /* Three-wire mode, USI software clock */
    USICR = (1<<USIWM0) | (1<<USICLK);
}

/**
 * @brief Assert the CS pin.
 *
 * @note Doesn't check for CS already asserted.
 */
void Spi::enableCs()
{
    /* Assert CS pin */
    if (m_cs != nullptr) {
        m_cs->assert();
    }
}

/**
 * @brief Deassert CS pin.
 *
 * @note Doesn't check for CS already deasserted.
 */
void Spi::disableCs()
{
    /* Deassert CS pin */
    if (m_cs != nullptr) {
        m_cs->deassert();
    }
}

/**
 * @brief Write to the SPI bus and return the received bytes.
 *
 * @note Both `read_bytes` and `write_bytes` may not be nullptr.
 *
 * @param[out] read_bytes
 *             The bytes received while writing. May be nullptr only if `write_bytes` is not nullptr.
 *             Causes received bytes to be ignored.
 * @param[in]  write_bytes
 *             The bytes to be written to the bus. May be nullptr only if `read_bytes` is not nullptr.
 *             Causes `0` to be written and received bytes to be stored in `read_bytes`.
 * @param[in]  num_bytes
 *             The number of bytes in the write_bytes buffer.
 * @return The number of bytes written/received. If zero, either `num_bytes` was zero or an error
 *         occurred.
 */
size_t Spi::transfer( uint8_t * const read_bytes,
                      const uint8_t * const write_bytes,
                      const size_t num_bytes )
{
    const uint8_t USICR_TICK = (m_mode == Mode::MODE_0) ?
                               (1<<USIWM0) | (1<<USICS1) | (1<<USICLK) | (1<<USITC) :
                               (1<<USIWM0) | (1<<USICS1) | (1<<USICS0) | (1<<USICLK) | (1<<USITC);
    size_t bytes_written = 0;

    if( (read_bytes == nullptr) && (write_bytes == nullptr) ) {
        /* Both read_bytes and write_bytes cannot be nullptr */
        return 0;
    }

    while( bytes_written < num_bytes ) {
        if( write_bytes != nullptr ) {
            /* Write byte to USI register */
            USIDR = write_bytes[bytes_written];
        } else {
            USIDR = 0x00;
        }

        /* Clear 4-bit counter and overflow flag */
        USISR = (1<<USIOIF);

        // This loop takes approximately 5 cycles
        while( (USISR & (1<<USIOIF)) == 0 )
        {
            /* Strobe clock and shift next bit out */
            USICR = USICR_TICK;
        }

        if( read_bytes != nullptr )
        {
            read_bytes[bytes_written] = USIDR;
        }

        bytes_written++;
    }

    return bytes_written;
}

/**
 * @brief Write the given buffer of bytes to the SPI bus.
 *
 * Writes the bytes to the bus while ignoring the bytes returned from the slave.
 *
 * @param[in]  write_bytes
 *             A pointer to the buffer of bytes to write.
 * @param[in]  num_bytes
 *             The number of bytes to write.

 * @return The number of bytes written. Or zero if something failed.
 */
size_t Spi::write( const uint8_t * const write_bytes, const size_t num_bytes )
{
    return transfer( nullptr, write_bytes, num_bytes );
}

/**
 * @brief Read bytes from the slave into the given buffer.
 *
 * Reads bytes from the slave into the supplied buffer. Sends zeros to force the slave to write.
 *
 * @param[out] read_bytes
 *             A pointer to the buffer to store the read bytes into.
 * @param[in]  num_bytes
 *             The number of bytes to read.

 * @return The number of bytes read. Or zero if something failed.
 */
size_t Spi::read( uint8_t * const read_bytes, const size_t num_bytes )
{
    return transfer( read_bytes, nullptr, num_bytes );
}

} // namespace hal
} // namespace junk
