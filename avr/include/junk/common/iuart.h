/**
 * @file      iuart.h
 * @brief     This file contains the common uart driver interface.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-10-09
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_IUART_H
#define JUNK_IUART_H

#include <stdbool.h>

namespace junk {

class IUart {
public:
    virtual bool putChar( const char c ) = 0;
    virtual char getChar() = 0;
    virtual size_t write( const char* const buffer, const size_t buffer_size ) = 0;
    virtual size_t write( const char* const buffer,
                          const size_t buffer_size,
                          const uint16_t timeout_ms ) = 0;
    virtual size_t read( char* const buffer, const size_t read_size ) = 0;
    virtual size_t read( char* const buffer,
                         const size_t read_size,
                         const uint16_t timeout_ms ) = 0;
};

} // namespace junk

#endif /* JUNK_IUART_H */
