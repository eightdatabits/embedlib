/**
 * @file      spi.h
 * @brief     This file contains the SPI driver declaration for the AVR ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_SPI_ATTINYx5_H
#define JUNK_SPI_ATTINYx5_H

#include <stddef.h>
#include <stdint.h>

#include "junk/hal/ispi.h"
#include "junk/hal/attinyx5/pin.h"

namespace junk {
namespace hal {

/**
 * @brief SPI master driver.
 *
 * This SPI driver represents a master device on an SPI bus. It adheres the the ISpi interface and
 * provides functions to send bytes, read bytes, and do a concurrent send and read.
 *
 * ## Mode ##
 *
 * The bus may either be mode 0 or mode 1. These are the only modes supported by the USI peripheral.
 *
 * ## Frequency ##
 *
 * The driver does not allow setting the bus frequency because it must be set via software sleeps.
 * The minimum sleep possible is 15 cycles via `junk_delay_cycles`. This delay along with 5 cycles
 * for the bit toggle loop means that there is a minimum 20 cycle half-bit rate. A 40 cycle bit rate
 * at 16MHz system clock leads to a maximum selectable bus frequency of 400kHz. At 1MHz system clock
 * the maximum selectable bus frequency is 25kHz.
 *
 * Due to such low frequencies, it didn't make sense to provide a mechanism to select the bus
 * frequency. Instead the frequency is locked at the maximum possible bus frequency. These
 * frequencies are listed in the table below.
 *
 * System Clock | Bus Frequency
 * -------------|--------------
 * 16MHz        | 1.6MHz
 * 10MHz        | 1MHz
 * 8MHz         | 800kHz
 * 4MHz         | 400kHz
 * 2MHz         | 200kHz
 * 1MHz         | 100kHz
 */
class Spi : public ISpi {
public:
    /**
     * @brief The SPI modes that this driver provides.
     *
     * Only mode 0 and mode 1 are supported since that is all the USI peripheral supports.
     */
    enum class Mode
    {
        MODE_0 = 0U, ///< CPOL = 0, CPHA = 0
        MODE_1 = 1U  ///< CPOL = 0, CPHA = 1
    };

    Spi(Mode mode, Pin* cs = nullptr);
    virtual ~Spi() = default;

    /**
     * @brief Set the SPI mode of the bus.
     *
     * @param[in]  mode
     *             The mode the bus should use. Applies to the next transfer.
     */
    void setMode(Mode mode) { m_mode = mode; };
    /**
     * @brief Get the currently set bus mode.
     *
     * @return The currently set bus mode.
     */
    Mode getMode() const { return m_mode; };
    void enableCs() override final;
    void disableCs() override final;
    size_t transfer( uint8_t * const read_bytes,
                     const uint8_t * const write_bytes,
                     const size_t num_bytes ) override final;
    size_t write( const uint8_t * const write_bytes,
                  const size_t num_bytes ) override final;
    size_t read( uint8_t * const read_bytes,
                 const size_t num_bytes ) override final;

private:
    /**
     * @brief The PORTB pin used for MOSI.
     *
     * @warning The datasheet indicates MOSI is on PB0, but we care about DO here which is PB1.
     */
    static constexpr uint8_t PIN_MOSI = 1;
    /**
     * @brief The PORTB pin used for MISO.
     *
     * @warning The datasheet indicates MISO is on PB1, but we care about DI here which is PB0.
     */
    static constexpr uint8_t PIN_MISO = 0;
    /**
     * @brief The PORTB pin used for SCLK.
     */
    static constexpr uint8_t PIN_SCLK = 2;

    Mode m_mode = Mode::MODE_0;
    Pin* m_cs = nullptr;
};

} // namespace hal
} // namespace junk

#endif /* JUNK_SPI_ATTINYx5_H */
