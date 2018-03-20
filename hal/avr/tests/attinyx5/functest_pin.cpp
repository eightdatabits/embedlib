/**
 * @file      functest_pin.cpp
 * @brief     This file contains tests for ATtinyx5 series pin driver.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-09-22
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stdint.h>

#include "junk/hal/attinyx5/delay.h"
#include "junk/hal/attinyx5/pin.h"

using namespace junk::hal;

void functest();

int main(int argc, char** argv)
{
    functest();

    return 0;
}

/**
 * @brief The ATTinyx5 family Pin driver functional test.
 *
 * ## Hardware Setup
 *
 * - Use the MikroElektronica EasyAVRv7.
 * - Put an ATTinyx5 chip in one of the DIP slots.
 * - Connect an AVR-ISP or similar programmer.
 * - Ensure PORTB LEDs are ON (SW10).
 * - Button press levels (SW1) should be VCC.
 * - Add a pull-down to PB1.
 *
 * ## Expected Results
 *
 * - Initially, all LEDs except PB4 should be off.
 * - While PB1 button is pressed:
 *   - PB0 will turn on.
 *   - PB2 will be toggling, but it is too fast to see.
 *   - PB4 will turn off.
 * - When PB1 is released:
 *   - PB0 will turn off.
 *   - PB2 will be in an indeterminate state (could be off or on).
 *   - PB4 will turn on.
 *
 */
void functest()
{
    Pin pb0(0);
    Pin pb1(1, true);
    Pin pb2(2, true);
    Pin pb4(4, false);
    pb0.setDirection(Pin::Direction::OUT);
    pb1.setDirection(Pin::Direction::IN);
    pb2.setDirection(Pin::Direction::OUT);
    pb4.setDirection(Pin::Direction::OUT);

    while(true) {
        if (pb1.read()) {
            pb0.assert();
            pb4.assert();
            pb2.toggle();
        } else {
            pb0.deassert();
            pb4.deassert();
        }
    }
}