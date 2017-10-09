/**
 * @file      ispi.h
 * @brief     This file contains the common SPI driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef EMB_ISPI_H
#define EMB_ISPI_H

#include <stdbool.h>
#include <stdint.h>

namespace emb {

class ISpi {
public:
    virtual bool enableCs() = 0;
    virtual bool disableCs() = 0;
    virtual size_t writeRead( uint8_t * const read_bytes,
                              const uint8_t * const write_bytes,
                              const size_t num_bytes ) = 0;
    virtual size_t write( const uint8_t * const write_bytes,
                          const size_t num_bytes ) = 0;
    virtual size_t read( uint8_t * const read_bytes,
                         const size_t num_bytes ) = 0;
};

} // namespace emb

#endif /* EMB_ISPI_H */
