/**
 * @file      io.h
 * @brief     This file contains the IO mocks for the ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-09-22
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef MOCK_IO_H
#define MOCK_IO_H

#include <stdint.h>

/* I/O registers */

/* Reserved [0x00..0x02] */

extern uint8_t ADCSRB;
#define BIN     7
#define ACME    6
#define IPR     5
#define ADTS2   2
#define ADTS1   1
#define ADTS0   0

extern uint16_t ADCW;
#define ADCL (*(&ADCW))
#define ADCH (*((&ADCW)+1))

extern uint8_t ADCSRA;
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

extern uint8_t ADMUX;
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define REFS2   4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

extern uint8_t ACSR;
#define ACD     7
#define ACBG    6
#define ACO     5
#define ACI     4
#define ACIE    3
#define ACIS1   1
#define ACIS0   0

/* Reserved [0x09..0x0C] */

extern uint8_t USICR;
#define USISIE  7
#define USIOIE  6
#define USIWM1  5
#define USIWM0  4
#define USICS1  3
#define USICS0  2
#define USICLK  1
#define USITC   0

extern uint8_t USISR;
#define USISIF  7
#define USIOIF  6
#define USIPF   5
#define USIDC   4
#define USICNT3 3
#define USICNT2 2
#define USICNT1 1
#define USICNT0 0

extern uint8_t USIDR;
extern uint8_t USIBR;

extern uint8_t GPIOR0;
extern uint8_t GPIOR1;
extern uint8_t GPIOR2;

extern uint8_t DIDR0;
#define ADC0D   5
#define ADC2D   4
#define ADC3D   3
#define ADC1D   2
#define AIN1D   1
#define AIN0D   0

extern uint8_t PCMSK;
#define PCINT5  5
#define PCINT4  4
#define PCINT3  3
#define PCINT2  2
#define PCINT1  1
#define PCINT0  0

extern uint8_t PINB;
#define PINB5   5
#define PINB4   4
#define PINB3   3
#define PINB2   2
#define PINB1   1
#define PINB0   0

extern uint8_t DDRB;
#define DDB5    5
#define DDB4    4
#define DDB3    3
#define DDB2    2
#define DDB1    1
#define DDB0    0

extern uint8_t PORTB;
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* Reserved [0x19..0x1B] */

/* EEPROM Control Register EECR */
extern uint8_t EECR;
#define EEPM1   5
#define EEPM0   4
#define EERIE   3
#define EEMPE   2
#define EEPE    1
#define EERE    0

/* EEPROM Data Register */
extern uint8_t EEDR;

/* EEPROM Address Register */
extern uint16_t EEAR;
#define EEARL (*(&EEAR))
#define EEARH (*((&EEAR)+1))

extern uint8_t PRR;
#define PRTIM1  3
#define PRTIM0  2
#define PRUSI   1
#define PRADC   0

extern uint8_t WDTCR;
#define WDIF    7
#define WDIE    6
#define WDP3    5
#define WDCE    4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

extern uint8_t DWDR;

extern uint8_t DTPS1;
#define DTPS11   1
#define DTPS10   0

extern uint8_t DT1B;
#define DT1BH3  7
#define DT1BH2  6
#define DT1BH1  5
#define DT1BH0  4
#define DT1BL3  3
#define DT1BL2  2
#define DT1BL1  1
#define DT1BL0  0

extern uint8_t DT1A;
#define DT1AH3  7
#define DT1AH2  6
#define DT1AH1  5
#define DT1AH0  4
#define DT1AL3  3
#define DT1AL2  2
#define DT1AL1  1
#define DT1AL0  0

extern uint8_t CLKPR;
#define CLKPCE  7
#define CLKPS3  3
#define CLKPS2  2
#define CLKPS1  1
#define CLKPS0  0

extern uint8_t PLLCSR;
#define LSM     7
#define PCKE    2
#define PLLE    1
#define PLOCK   0

extern uint8_t OCR0B;

extern uint8_t OCR0A;

extern uint8_t TCCR0A;
#define COM0A1  7
#define COM0A0  6
#define COM0B1  5
#define COM0B0  4
#define WGM01   1
#define WGM00   0

extern uint8_t OCR1B;

extern uint8_t GTCCR;
#define TSM     7
#define PWM1B   6
#define COM1B1  5
#define COM1B0  4
#define FOC1B   3
#define FOC1A   2
#define PSR1    1
#define PSR0    0

extern uint8_t OCR1C;

extern uint8_t OCR1A;

extern uint8_t TCNT1;

extern uint8_t TCCR1;
#define CTC1    7
#define PWM1A   6
#define COM1A1  5
#define COM1A0  4
#define CS13    3
#define CS12    2
#define CS11    1
#define CS10    0

extern uint8_t OSCCAL;

extern uint8_t TCNT0;

extern uint8_t TCCR0B;
#define FOC0A   7
#define FOC0B   6
#define WGM02   3
#define CS02    2
#define CS01    1
#define CS00    0

extern uint8_t MCUSR;
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

extern uint8_t MCUCR;
#define BODS    7
#define PUD     6
#define SE      5
#define SM1     4
#define SM0     3
#define BODSE   2
#define ISC01   1
#define ISC00   0

/* Reserved [0x36] */

extern uint8_t SPMCSR;
#define RSIG    5
#define CTPB    4
#define RFLB    3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

extern uint8_t TIFR;
#define OCF1A   6
#define OCF1B   5
#define OCF0A   4
#define OCF0B   3
#define TOV1    2
#define TOV0    1

extern uint8_t TIMSK;
#define OCIE1A  6
#define OCIE1B  5
#define OCIE0A  4
#define OCIE0B  3
#define TOIE1   2
#define TOIE0   1

extern uint8_t GIFR;
#define INTF0   6
#define PCIF    5

extern uint8_t GIMSK;
#define INT0    6
#define PCIE    5

/* Reserved [0x3C] */

/* 0x3D..0x3E SP  [defined in <avr/io.h>] */
/* 0x3F SREG      [defined in <avr/io.h>] */

#endif // MOCK_IO_H
