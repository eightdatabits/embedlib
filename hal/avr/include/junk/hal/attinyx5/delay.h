/**
 * @file      delay.h
 * @brief     This file contains delays for the ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-10-09
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef JUNK_DELAY_H
#define JUNK_DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void junk_delay_cycles(uint16_t i);

#ifdef __cplusplus
}
#endif

#endif // JUNK_DELAY_H
