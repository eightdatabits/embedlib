/**
 * @file      stdcpp.cpp
 * @brief     This file contains some missing C++ standard library components.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-02-15
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stdlib.h>

void * operator new(size_t n)
{
  void * const p = malloc(n);
  // handle p == 0
  return p;
}

void operator delete(void * p)
{
  free(p);
}

extern "C" void __cxa_pure_virtual()
{
    while (1);
}
