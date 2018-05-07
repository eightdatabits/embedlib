/**
 * @file      test_binary_search.cpp
 * @brief     This file contains tests for binarySearch.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-04-21
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

#include "junk/algorithms/binary_search.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <vector>

using namespace junk::algorithms;

constexpr int compare(int a, int b)
{
    return ((a < b) ? -1 :
            ((a == b) ? 0 : 1));
}

template <typename T>
T* linearSearch(T* const array, const size_t length, const T& match)
{
    for (size_t i = 0; i < length; i++) {
        if (array[i] == match) {
            return &array[i];
        }
    }

    return nullptr;
}

void test_null();
void test_empty();
void test_leftmost();
void test_rightmost();
void test_middle_odd();
void test_middle_even_left();
void test_middle_even_right();
void test_fuzzy_search();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_null);
    RUN_TEST(test_empty);
    RUN_TEST(test_leftmost);
    RUN_TEST(test_rightmost);
    RUN_TEST(test_middle_odd);
    RUN_TEST(test_middle_even_left);
    RUN_TEST(test_middle_even_right);
    RUN_TEST(test_fuzzy_search);

    return UNITY_END();
}

void test_null()
{
    TEST_ASSERT_NULL(binarySearch((int*)nullptr, 10, 1));
    TEST_ASSERT_NULL(binarySearch((int*)nullptr, 10U, 1, &compare));
}

void test_empty()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    TEST_ASSERT_NULL(binarySearch(&array[0], 0, 1));
    TEST_ASSERT_NULL(binarySearch(&array[0], 0, 1, &compare));
}

void test_leftmost()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int* result = binarySearch(&array[0], 10, 0);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, *result);

    result = binarySearch(array, 0);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, *result);

    result = binarySearch(&array[0], 10, 0, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, *result);

    result = binarySearch(array, 0, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, *result);
}

void test_rightmost()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int* result = binarySearch(&array[0], 10, 9);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(9, *result);

    result = binarySearch(array, 9);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(9, *result);

    result = binarySearch(&array[0], 10, 9, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(9, *result);

    result = binarySearch(array, 9, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(9, *result);
}

void test_middle_odd()
{
    int array[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int* result = binarySearch(&array[0], 11, 5);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(array, 5);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(&array[0], 11, 5, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(array, 5, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);
}

void test_middle_even_left()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int* result = binarySearch(&array[0], 10, 4);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(4, *result);

    result = binarySearch(array, 4);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(4, *result);

    result = binarySearch(&array[0], 10, 4, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(4, *result);

    result = binarySearch(array, 4, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(4, *result);
}

void test_middle_even_right()
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int* result = binarySearch(&array[0], 10, 5);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(array, 5);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(&array[0], 10, 5, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);

    result = binarySearch(array, 5, &compare);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(5, *result);
}

void test_fuzzy_search()
{
#ifdef FUZZ_SEED
    uint32_t seed = FUZZ_SEED;
#else
    uint32_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
#endif
    std::cout << "Fuzz seed: " << seed << std::endl;
    srand(seed);

    const size_t samples = 100000;
    for (uint32_t s = 8; s <= (1<<20); s *= 2) {
        const size_t kArraySize = s;
        std::cout << "Array size: " << kArraySize << std::endl;
        int *array = new int[kArraySize];
        std::set<int> unique;
        std::vector<int> nums;
        while(unique.size() < kArraySize) {
            auto p = unique.insert(rand());
            if (p.second == false) {
                //std::cout << "Collision: " << *p.first << std::endl;
            }
        }

        // Fill array with unique random numbers
        uint32_t i = 0;
        for (auto iter = unique.begin(); iter != unique.end(); iter++, i++) {
            nums.push_back(*iter);
            array[i] = *iter;
        }

        std::cout << "Samples: " << samples << std::endl;

        double sum1 = 0.0;
        double sum2 = 0.0;
        double sum3 = 0.0;
        for (uint32_t i = 0; i < samples; i++) {
            size_t index = rand() % kArraySize;

            // Time the binary search function
            auto start1 = std::chrono::high_resolution_clock::now();
            int* result1 = binarySearch(&array[0], kArraySize, nums[index]);
            auto end1 = std::chrono::high_resolution_clock::now();

            TEST_ASSERT_NOT_NULL(result1);
            TEST_ASSERT_EQUAL_INT(nums[index], *result1);

            // Time the std::binary_search function
            auto start2 = std::chrono::high_resolution_clock::now();
            bool result2 = std::binary_search(&array[0], &array[kArraySize], nums[index]);
            auto end2 = std::chrono::high_resolution_clock::now();

            TEST_ASSERT_TRUE(result2);

            // Time the linear search function
            auto start3 = std::chrono::high_resolution_clock::now();
            int* result3 = linearSearch(&array[0], kArraySize, nums[index]);
            auto end3 = std::chrono::high_resolution_clock::now();

            TEST_ASSERT_NOT_NULL(result3);
            TEST_ASSERT_EQUAL_INT(nums[index], *result3);

            uint64_t diff1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();
            uint64_t diff2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
            uint64_t diff3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count();

            sum1 += diff1;
            sum2 += diff2;
            sum3 += diff3;
        }

        std::cout << "binarySearch avg: " << sum1 / samples << "ns" << std::endl;
        std::cout << "std::binary_search avg: " << sum2 / samples << "ns" << std::endl;
        std::cout << "linearSearch avg: " << sum3 / samples << "ns" << std::endl;
        std::cout << std::endl;

        delete array;
    }
}
