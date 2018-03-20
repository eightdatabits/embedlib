/**
 * @file      functest_spi.cpp
 * @brief     This file contains functional tests for ATtinyx5 series SPI driver.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-02-16
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include <stdint.h>
#include <avr/io.h>

#include "junk/hal/attinyx5/delay.h"
#include "junk/hal/attinyx5/spi.h"

using namespace junk::hal;

void functest();

int main(int argc, char** argv)
{
    functest();

    return 0;
}

/**
 * @brief The ATTinyx5 family SPI driver functional test.
 *
 * ## Hardware Setup
 *
 * - Use the MikroElektronica EasyAVRv7.
 * - Put an ATTinyx5 chip in one of the DIP slots.
 * - Connect an AVR-ISP or similar programmer.
 * - Ensure PORTB LEDs are OFF (SW10).
 * - Connect Saleae to the following pins:
 *   - Gray -> GND
 *   - Black -> PB1 (MOSI)
 *   - Brown -> PB0 (MISO)
 *   - Red -> PB2 (SCLK)
 *   - Orange -> PB4 (nCS)
 *
 * ## Expected Results
 *
 * - Recording on the Saleae should produce an SPI frame of 'h','e','l','l','o'. The bus frequency
 *   should be 800kHz with a system clock of 8MHz.
 * - Time between frames should be at least 12usec (likely more due to overhead).
 */
void functest()
{
    uint8_t out[] = {'h','e','l','l','o'};
    Pin cs(4, false);
    Spi spi(Spi::Mode::MODE_0, &cs);

    while(true) {
        spi.enableCs();
        spi.write(&out[0], sizeof(out));
        spi.disableCs();
        junk_delay_cycles(100);
    }
}