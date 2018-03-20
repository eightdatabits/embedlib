/**
 * @file      ispi.h
 * @brief     This file contains the common SPI driver interface.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_ISPI_H
#define JUNK_ISPI_H

#include <stddef.h>
#include <stdint.h>

namespace junk {
namespace hal {

class ISpi {
public:
    virtual void enableCs() = 0;
    virtual void disableCs() = 0;
    virtual size_t transfer( uint8_t * const read_bytes,
                             const uint8_t * const write_bytes,
                             const size_t num_bytes ) = 0;
    virtual size_t write( const uint8_t * const write_bytes,
                          const size_t num_bytes ) = 0;
    virtual size_t read( uint8_t * const read_bytes,
                         const size_t num_bytes ) = 0;
};

} // namespace hal
} // namespace junk

#endif /* JUNK_ISPI_H */
