/**
 * @file      test_pin_attinyx5.c
 * @brief     This file contains tests for ATtinyx5 series pin driver.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-09-22
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include <stdio.h>

#include "unity.h"

#include "embedlib/common/pin.h"

void test_first(void)
{
    TEST_FAIL();
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_first);

    return UNITY_END();
}
