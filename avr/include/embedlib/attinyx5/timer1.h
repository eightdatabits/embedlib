/**
 * @file   timer.h
 * @brief  This file contains the common timer driver declarations for the AVR ATtinyx5 series.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2015-09-13
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef EMB_TIMER1_ATTINYx5_H
#define EMB_TIMER1_ATTINYx5_H

#include <stdbool.h>
#include <stdint.h>

#include "embedlib/common/itimer.h"

namespace emb {

class Timer1 : public ITimer {
public:
    enum Prescaler
    {
        PRE_OFF   = 0U,
        PRE_1     = 1U,
        PRE_2     = 2U,
        PRE_4     = 3U,
        PRE_8     = 4U,
        PRE_16    = 5U,
        PRE_32    = 6U,
        PRE_64    = 7U,
        PRE_128   = 8U,
        PRE_256   = 9U,
        PRE_512   = 10U,
        PRE_1024  = 11U,
        PRE_2048  = 12U,
        PRE_4096  = 13U,
        PRE_8192  = 14U,
        PRE_16384 = 15U
    };

    Timer1( Prescaler pre, bool reset_on_match );
    ~Timer1();

    virtual bool start();
    virtual bool pause();
    virtual bool reset();

    bool isRunning() const;
    bool setPrescaler( Prescaler pre );
    bool setCounter( const uint8_t value );
    uint8_t getCounter() const;
    bool enableIrq();
    bool disableIrq();
    bool setCompare( const uint8_t value );
    uint8_t getCompare() const;

private:
    Prescaler m_prescaler;
};

} // namespace emb

#endif /* EMB_TIMER1_ATTINYx5_H */