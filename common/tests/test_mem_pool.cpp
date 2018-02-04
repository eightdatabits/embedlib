/**
 * @file      test_mem_pool.cpp
 * @brief     This file contains tests for MemPool.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-12-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

#include "junk/common/mem_pool.h"

using namespace junk;

void test_allocate_success();
void test_deallocate_success();
void test_allocate_full();
void test_deallocate_empty();
void test_deallocate_null();
void test_deallocate_invalid();
void test_alignment_2();
void test_alignment_4();
void test_alignment_8();
void test_alignment_16();
void test_alignment_32();
void test_alignment_64();
void test_alignment_128();
void test_bucket_size_1();
void test_bucket_size_2();
void test_bucket_size_4();
void test_bucket_size_8();
void test_bucket_size_16();
void test_bucket_size_32();
void test_bucket_size_64();
void test_bucket_size_128();
void test_bucket_size_256();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_allocate_success);
    RUN_TEST(test_deallocate_success);
    RUN_TEST(test_allocate_full);
    RUN_TEST(test_deallocate_empty);
    RUN_TEST(test_deallocate_null);
    RUN_TEST(test_deallocate_invalid);
    RUN_TEST(test_alignment_2);
    RUN_TEST(test_alignment_4);
    RUN_TEST(test_alignment_8);
    RUN_TEST(test_alignment_16);
    RUN_TEST(test_alignment_32);
    RUN_TEST(test_alignment_64);
    RUN_TEST(test_alignment_128);
    RUN_TEST(test_bucket_size_1);
    RUN_TEST(test_bucket_size_2);
    RUN_TEST(test_bucket_size_4);
    RUN_TEST(test_bucket_size_8);
    RUN_TEST(test_bucket_size_16);
    RUN_TEST(test_bucket_size_32);
    RUN_TEST(test_bucket_size_64);
    RUN_TEST(test_bucket_size_128);
    RUN_TEST(test_bucket_size_256);

    return UNITY_END();
}

void test_allocate_success()
{
    MemPool<sizeof(uint32_t), 1> uut;
    TEST_ASSERT(nullptr != uut.allocate(sizeof(uint32_t)));
}

void test_deallocate_success()
{
    MemPool<sizeof(uint32_t), 1> uut;
    void* mem = uut.allocate(sizeof(uint32_t));
    TEST_ASSERT(nullptr != mem);
    uut.deallocate(mem);
    void* mem2 = uut.allocate(sizeof(uint32_t));
    TEST_ASSERT(mem == mem2);
}

void test_allocate_full()
{
    MemPool<sizeof(uint32_t), 1> uut;
    TEST_ASSERT(nullptr != uut.allocate(sizeof(uint32_t)));
    TEST_ASSERT(nullptr == uut.allocate(sizeof(uint32_t)));
}

void test_deallocate_empty()
{
    MemPool<sizeof(uint32_t), 1> uut;
    void* mem = uut.allocate(sizeof(uint32_t));
    TEST_ASSERT(nullptr != mem);
    uut.deallocate(mem);
    uut.deallocate(mem);
}

void test_deallocate_null() {
    MemPool<sizeof(uint32_t), 1> uut;
    uut.deallocate(nullptr);
}

void test_deallocate_invalid() {
    MemPool<sizeof(uint32_t), 1> uut;
    void* mem = uut.allocate(sizeof(uint32_t));
    TEST_ASSERT(nullptr != mem);
    uut.deallocate(static_cast<uint8_t*>(mem) + 1);
    TEST_ASSERT(nullptr == uut.allocate(sizeof(uint32_t))); // Allocation should fail since deallocation failed
}

void test_alignment_2()
{
    MemPool<sizeof(uint8_t), 2, 2> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 2) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 2) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_4()
{
    MemPool<sizeof(uint8_t), 2, 4> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 4) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 4) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_8()
{
    MemPool<sizeof(uint8_t), 2, 8> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 8) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 8) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_16()
{
    MemPool<sizeof(uint8_t), 2, 16> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 16) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 16) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_32()
{
    MemPool<sizeof(uint8_t), 2, 32> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 32) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 32) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_64()
{
    MemPool<sizeof(uint8_t), 2, 64> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 64) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 64) == reinterpret_cast<uintptr_t>(mem2));
}

void test_alignment_128()
{
    MemPool<sizeof(uint8_t), 2, 128> uut;
    void* mem1 = uut.allocate(sizeof(uint8_t));
    void* mem2 = uut.allocate(sizeof(uint8_t));
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) % 128) == 0);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem1) + 128) == reinterpret_cast<uintptr_t>(mem2));
}

void test_bucket_size_1()
{
    MemPool<1, 2, 1> uut;
    void* mem1 = uut.allocate(1);
    void* mem2 = uut.allocate(1);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 1);
}

void test_bucket_size_2()
{
    MemPool<2, 2, 1> uut;
    void* mem1 = uut.allocate(2);
    void* mem2 = uut.allocate(2);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 2);
}

void test_bucket_size_4()
{
    MemPool<4, 2, 1> uut;
    void* mem1 = uut.allocate(4);
    void* mem2 = uut.allocate(4);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 4);
}

void test_bucket_size_8()
{
    MemPool<8, 2, 1> uut;
    void* mem1 = uut.allocate(8);
    void* mem2 = uut.allocate(8);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 8);
}

void test_bucket_size_16()
{
    MemPool<16, 2, 1> uut;
    void* mem1 = uut.allocate(16);
    void* mem2 = uut.allocate(16);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 16);
}

void test_bucket_size_32()
{
    MemPool<32, 2, 1> uut;
    void* mem1 = uut.allocate(32);
    void* mem2 = uut.allocate(32);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 32);
}

void test_bucket_size_64()
{
    MemPool<64, 2, 1> uut;
    void* mem1 = uut.allocate(64);
    void* mem2 = uut.allocate(64);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 64);
}

void test_bucket_size_128()
{
    MemPool<128, 2, 1> uut;
    void* mem1 = uut.allocate(128);
    void* mem2 = uut.allocate(128);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 128);
}

void test_bucket_size_256()
{
    MemPool<256, 2, 1> uut;
    void* mem1 = uut.allocate(256);
    void* mem2 = uut.allocate(256);
    TEST_ASSERT(nullptr != mem1);
    TEST_ASSERT(nullptr != mem2);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(mem2) - reinterpret_cast<uintptr_t>(mem1)) == 256);
}
