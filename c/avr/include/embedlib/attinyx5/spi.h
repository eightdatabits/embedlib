/**
 * @file      spi.h
 * @brief     This file contains the SPI driver declaration for the AVR ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef EMB_SPI_ATTINYx5_H
#define EMB_SPI_ATTINYx5_H

#include <stdbool.h>
#include <stdint.h>

#include "embedlib/common/spi.h"
#include "embedlib/attinyx5/pin.h"

namespace emb {

class Spi : public ISpi {
public:
    enum BaudRate
    {
        BAUD_100K = 0U,
        BAUD_200K = 1U,
        BAUD_500K = 2U,
        BAUD_1M   = 3U
    };

    enum Mode
    {
        MODE_0 = 0U,
        MODE_1 = 1U,
        MODE_2 = 2U,
        MODE_3 = 3U
    };

    Spi(Pin& cs, Pin& mosi, Pin& miso, Pin& sclk);
    virtual ~Spi() {};

    bool setBaudRate(BaudRate baud);
    bool setMode(Mode mode);
    virtual bool enableCs();
    virtual bool disableCs();
    virtual size_t writeRead( uint8_t * const read_bytes,
                              const uint8_t * const write_bytes,
                              const size_t num_bytes );
    virtual size_t write( const uint8_t * const write_bytes,
                          const size_t num_bytes );
    virtual size_t read( uint8_t * const read_bytes,
                         const size_t num_bytes );

private:
    BaudRate m_baudrate;
    Mode m_mode;

    Pin& m_cs;
    Pin& m_mosi;
    Pin& m_miso;
    Pin& m_sclk;
};

} // namespace emb

#endif /* EMB_SPI_ATTINYx5_H */
