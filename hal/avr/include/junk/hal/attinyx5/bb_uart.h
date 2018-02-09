/**
 * @file   bb_uart.h
 * @brief  This file contains the bit-banged UART driver for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-09
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_BB_UART_ATTINYx5_H
#define JUNK_BB_UART_ATTINYx5_H

#include <stdbool.h>
#include <stdint.h>

#include "junk/hal/iuart.h"
#include "junk/hal/attinyx5/pin.h"

namespace junk {
namespace hal {

class BitBangUart : public IUart {
public:
    enum Baud
    {
        BAUD_1200  = 0U,
        BAUD_2400  = 1U,
        BAUD_4800  = 2U,
        BAUD_9600  = 3U,
        BAUD_19200 = 4U
    };

    BitBangUart( Baud baud, Pin* rx = NULL, Pin* tx = NULL );
    ~BitBangUart();

    virtual bool putChar( const char c );
    virtual char getChar();
    virtual size_t write( const char* const buffer, const size_t buffer_size );
    virtual size_t write( const char* const buffer,
                          const size_t buffer_size,
                          const uint16_t timeout_ms );
    virtual size_t read( char* const buffer, const size_t read_size );
    virtual size_t read( char* const buffer,
                         const size_t read_size,
                         const uint16_t timeout_ms );

private:
    static const uint8_t PIN_ASSERT_NUM_INSTR = 20U;
    Baud m_baud;
    Pin* m_rx;
    Pin* m_tx;
};

} // namespace hal
} // namespace junk

#endif /* JUNK_BB_UART_ATTINYx5_H */