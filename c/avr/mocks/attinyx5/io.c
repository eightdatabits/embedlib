/**
 * @file      io.c
 * @brief     This file contains the IO mocks for the ATtinyx5 series.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-09-22
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <avr/io.h>

uint8_t ADCSRB;
uint16_t ADCW;
uint8_t ADCSRA;
uint8_t ADMUX;
uint8_t ACSR;

/* Reserved [0x09..0x0C] */

uint8_t USICR;
uint8_t USISR;
uint8_t USIDR;
uint8_t USIBR;
uint8_t GPIOR0;
uint8_t GPIOR1;
uint8_t GPIOR2;
uint8_t DIDR0;
uint8_t PCMSK;
uint8_t PINB;
uint8_t DDRB;
uint8_t PORTB;

/* Reserved [0x19..0x1B] */

/* EEPROM Control Register EECR */
uint8_t EECR;

/* EEPROM Data Register */
uint8_t EEDR;

/* EEPROM Address Register */
uint16_t EEAR;

uint8_t PRR;
uint8_t WDTCR;
uint8_t DWDR;
uint8_t DTPS1;
uint8_t DT1B;
uint8_t DT1A;
uint8_t CLKPR;
uint8_t PLLCSR;
uint8_t OCR0B;
uint8_t OCR0A;
uint8_t TCCR0A;
uint8_t OCR1B;
uint8_t GTCCR;
uint8_t OCR1C;
uint8_t OCR1A;
uint8_t TCNT1;
uint8_t TCCR1;
uint8_t OSCCAL;
uint8_t TCNT0;
uint8_t TCCR0B;
uint8_t MCUSR;
uint8_t MCUCR;

/* Reserved [0x36] */

uint8_t SPMCSR;
uint8_t TIFR;
uint8_t TIMSK;
uint8_t GIFR;
uint8_t GIMSK;
