Junk
====
![](https://travis-ci.org/eightdatabits/junk.svg?branch=master)

A library containing a random assortment of useful embedded code. This includes a HAL with drivers
for AVR and STM32 parts as well as general use code such as memory, math, and container objects and
functions.

JunkHAL
-------

The JunkHAL currently only supports AVR processors. To build JunkHAL for all supported processors:
```
$ cd <junk_root>/hal/avr
$ make libs
```
Use `make help` to see all build options.
