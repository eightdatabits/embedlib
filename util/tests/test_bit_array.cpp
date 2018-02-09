/**
 * @file      test_bit_array.cpp
 * @brief     This file contains tests for BitArray.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-01-31
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

// Mock JUNK_TRAP
#define JUNK_TRAP(f,l) g_junk_assert_trap = true
bool g_junk_assert_trap = false;

#include "junk/containers/bit_array.h"

using namespace junk;

void test_default_constructor();
void test_init_constructor();
void test_readwrite_bit();
void test_readwrite_bits();
void test_at();
void test_size();
void test_bool();
void test_invert();
void test_toggle();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_default_constructor);
    RUN_TEST(test_init_constructor);
    RUN_TEST(test_readwrite_bit);
    RUN_TEST(test_readwrite_bits);
    RUN_TEST(test_at);
    RUN_TEST(test_size);
    RUN_TEST(test_bool);
    RUN_TEST(test_invert);
    RUN_TEST(test_toggle);

    return UNITY_END();
}

void test_default_constructor()
{
    BitArray<40> uut;

    for (uint8_t i = 0; i < 40; i++) {
        TEST_ASSERT(uut[i] == false);
    }
}

void test_init_constructor()
{
    BitArray<40> uut(true);

    for (uint32_t i = 0; i < 40; i++) {
        TEST_ASSERT(uut[i] == true);
    }

    BitArray<40> uut2(false);

    for (uint32_t i = 0; i < 40; i++) {
        TEST_ASSERT(uut2[i] == false);
    }
}

void test_readwrite_bit()
{
    BitArray<1> uut;
    const BitArray<1>& uut_ref = uut;

    TEST_ASSERT(uut[0] == false);
    TEST_ASSERT(uut_ref[0] == false);
    uut[0] = true;
    TEST_ASSERT(uut[0] == true);
    TEST_ASSERT(uut_ref[0] == true);
}

void test_readwrite_bits()
{
    BitArray<1000> uut;

    for (uint32_t i = 0; i < 1000; i++) {
        // Initialize values to pattern
        uut[i] = (bool)(i % 7);
    }

    const BitArray<1000>& uut_ref = uut;

    for (uint32_t i = 0; i < 1000; i++) {
        TEST_ASSERT(uut_ref[i] == (bool)(i % 7));
    }
}

void test_at()
{
    BitArray<1000> uut;

    for (uint32_t i = 0; i < 1000; i++) {
        uut[i] = (bool)(i % 6);
    }

    for (uint32_t i = 0; i < 1000; i++) {
        TEST_ASSERT(uut.at(i) == (bool)(i % 6));
    }

    (void)uut.at(1000);
    TEST_ASSERT(g_junk_assert_trap == true);
    g_junk_assert_trap = false;
}

void test_size()
{
    BitArray<1000> uut;

    TEST_ASSERT(uut.size() == 1000);
}

void test_bool()
{
    BitArray<1000> uut;

    TEST_ASSERT(!(bool)uut[0]);

    uut[0] = true;

    TEST_ASSERT((bool)uut[0]);
}

void test_invert()
{
    BitArray<1000> uut;

    TEST_ASSERT((~uut[0]) == true);

    uut[0] = true;

    TEST_ASSERT((~uut[0]) == false);
}

void test_toggle()
{
    BitArray<1000> uut;

    TEST_ASSERT(uut[0] == false);

    uut[0].toggle();

    TEST_ASSERT(uut[0] == true);

    uut[0].toggle().toggle();

    TEST_ASSERT(uut[0] == true);
}
