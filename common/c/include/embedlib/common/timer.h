/**
 * @file      timer.h
 * @brief     This file contains the common hardware timer driver declaration.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

/* Forward declaration of timer driver struct */
struct timer_s;
typedef struct timer_s timer_t;

bool timer_start( const timer_t * const timer );
bool timer_pause( const timer_t * const timer );
bool timer_reset( const timer_t * const timer );
bool timer_set( const timer_t * const timer, const uint8_t value );
bool timer_get( const timer_t * const timer, uint8_t * const value );

#endif /* TIMER_H */
