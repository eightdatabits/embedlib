/**
 * @file      pin.h
 * @brief     This file contains the pin driver definition for the AVR ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2015-08-29
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef EMB_ATTINYx5_PIN_H
#define EMB_ATTINYx5_PIN_H

#include <stdbool.h>

#include "embedlib/common/ipin.h"

namespace emb {

class Pin : public IPin {
public:
    typedef uint8_t PinNum;

    enum PuPd
    {
        PUPD_NONE     = 0U,
        PUPD_PULLDOWN = 1U,
        PUPD_PULLUP   = 2U
    };

    /* Note: There is only one pin bank in the ATTinyx5 family: bank B */
    Pin( const PinNum num, const bool asserted_high );
    virtual ~Pin() {};

    void setPuPd( const PuPd pupd );
    virtual void setDirection( const Direction dir );
    virtual bool read() const;
    virtual void assert();
    virtual void deassert();
    virtual void toggle();

private:
    PinNum m_num;
    bool m_asserted_high;
};

} // namespace emb

#endif /* EMB_ATTINYx5_PIN_H */
