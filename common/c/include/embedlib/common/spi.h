/**
 * @file      spi.h
 * @brief     This file contains the common SPI driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef SPI_H
#define SPI_H

#include <stdbool.h>
#include <stdint.h>

/* Forward declaration of SPI driver struct */
struct spi_s;
typedef struct spi_s spi_t;

bool spi_enable_cs( spi_t * const spi );
bool spi_disable_cs( spi_t * const spi );
bool spi_write_read( spi_t * const spi,
                     uint8_t * const read_bytes,
                     const uint8_t * const write_bytes,
                     const uint8_t num_bytes );
bool spi_write( spi_t * const spi,
                const uint8_t * const write_bytes,
                const uint8_t num_bytes );
bool spi_read( spi_t * const spi,
               uint8_t * const read_bytes,
               const uint8_t num_bytes );

#endif /* SPI_H */
