/**
 * @file      test_span.cpp
 * @brief     This file contains tests for Span.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-08-06
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

// Mock JUNK_TRAP
#define JUNK_TRAP(f,l) g_junk_assert_trap = true
bool g_junk_assert_trap = false;

#include "junk/containers/span.h"

using namespace junk;

void tearDown()
{
    g_junk_assert_trap = false;
}

void test_default_constructor();
void test_c_array_constructor_success();
void test_c_array_constructor_nullptr();
void test_c_array_constructor_zero_length();
void test_array_constructor();
void test_first_last_constructor();
void test_subscript_operator_success();
void test_subscript_operator_failure();
void test_const_subscript_operator_success();
void test_const_subscript_operator_failure();
void test_at_success();
void test_at_failure();
void test_const_at_success();
void test_const_at_failure();
void test_get();
void test_get_null();
void test_cget();
void test_cget_null();
void test_length();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_default_constructor);
    RUN_TEST(test_c_array_constructor_success);
    RUN_TEST(test_c_array_constructor_nullptr);
    RUN_TEST(test_c_array_constructor_zero_length);
    RUN_TEST(test_array_constructor);
    RUN_TEST(test_first_last_constructor);
    RUN_TEST(test_subscript_operator_success);
    RUN_TEST(test_subscript_operator_failure);
    RUN_TEST(test_const_subscript_operator_success);
    RUN_TEST(test_const_subscript_operator_failure);
    RUN_TEST(test_at_success);
    RUN_TEST(test_at_failure);
    RUN_TEST(test_const_at_success);
    RUN_TEST(test_const_at_failure);
    RUN_TEST(test_get);
    RUN_TEST(test_get_null);
    RUN_TEST(test_cget);
    RUN_TEST(test_cget_null);
    RUN_TEST(test_length);

    return UNITY_END();
}

void test_default_constructor()
{
    Span<uint32_t> uut;

    TEST_ASSERT_EQUAL_UINT32(0U, uut.length());
    TEST_ASSERT_EQUAL_PTR(nullptr, uut.get());
}

void test_c_array_constructor_success()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(&expected[0], 10);

    TEST_ASSERT_EQUAL_UINT32(10U, uut.length());
    TEST_ASSERT_EQUAL_PTR(&expected[0], uut.get());
    TEST_ASSERT_EQUAL_UINT32_ARRAY(&expected[0], uut.get(), 10U);
}

void test_c_array_constructor_nullptr()
{
    Span<uint32_t> fail(nullptr, 1);
    TEST_ASSERT_TRUE(g_junk_assert_trap);
    g_junk_assert_trap = false;
}

void test_c_array_constructor_zero_length()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(&expected[0], (size_t)0U);

    TEST_ASSERT_EQUAL_UINT32(0U, uut.length());
    TEST_ASSERT_EQUAL_PTR(&expected[0], uut.get());
}

void test_array_constructor()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    TEST_ASSERT_EQUAL_UINT32(10U, uut.length());
    TEST_ASSERT_EQUAL_PTR(&expected[0], uut.get());
    TEST_ASSERT_EQUAL_UINT32_ARRAY(&expected[0], uut.get(), 10U);
}

void test_first_last_constructor()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(&expected[0], &expected[9]);

    TEST_ASSERT_EQUAL_UINT32(10U, uut.length());
    TEST_ASSERT_EQUAL_PTR(&expected[0], uut.get());
    TEST_ASSERT_EQUAL_UINT32_ARRAY(&expected[0], uut.get(), 10U);
}

void test_subscript_operator_success()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_UINT32(expected[i], uut[i]);
        TEST_ASSERT_FALSE(g_junk_assert_trap);
    }
}

void test_subscript_operator_failure()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    (void)uut[10];
    TEST_ASSERT_TRUE(g_junk_assert_trap);
}

void test_const_subscript_operator_success()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_UINT32(expected[i], ((const Span<uint32_t>)uut)[i]);
        TEST_ASSERT_FALSE(g_junk_assert_trap);
    }
}

void test_const_subscript_operator_failure()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    (void)((const Span<uint32_t>)uut)[10];
    TEST_ASSERT_TRUE(g_junk_assert_trap);
}

void test_at_success()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_UINT32(expected[i], uut.at(i));
        TEST_ASSERT_FALSE(g_junk_assert_trap);
    }
}

void test_at_failure()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    (void)uut.at(10);
    TEST_ASSERT_TRUE(g_junk_assert_trap);
}

void test_const_at_success()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_UINT32(expected[i], ((const Span<uint32_t>)uut).at(i));
        TEST_ASSERT_FALSE(g_junk_assert_trap);
    }
}

void test_const_at_failure()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    (void)((const Span<uint32_t>)uut).at(10);
    TEST_ASSERT_TRUE(g_junk_assert_trap);
}

void test_get()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    TEST_ASSERT_EQUAL_PTR(&expected[0], uut.get());
}

void test_get_null()
{
    Span<uint32_t> uut;

    TEST_ASSERT_EQUAL_PTR(nullptr, uut.get());
}

void test_cget()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    TEST_ASSERT_EQUAL_PTR(&expected[0], ((const Span<uint32_t>)uut).cget());
}

void test_cget_null()
{
    Span<uint32_t> uut;

    TEST_ASSERT_EQUAL_PTR(nullptr, ((const Span<uint32_t>)uut).cget());
}

void test_length()
{
    uint32_t expected[10] = {1,2,3,4,5,6,7,8,9,10};
    Span<uint32_t> uut(expected);

    TEST_ASSERT_EQUAL_UINT32(10U, uut.length());
}
