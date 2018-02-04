/**
 * @file      test_queue.cpp
 * @brief     This file contains tests for Queue.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-02-01
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

// Mock EMB_TRAP
#define EMB_TRAP(f,l) g_emb_assert_trap = true
bool g_emb_assert_trap = false;

#include "embedlib/common/queue.h"

using namespace emb;

void test_empty();
void test_full();
void test_drain();
void test_wrap();
void test_peek();
void test_enqueue_move();
void test_emplace();
void test_trivial_type();
void test_pod_type();
void test_non_pod_type();
void test_derived_type();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_empty);
    RUN_TEST(test_full);
    RUN_TEST(test_drain);
    RUN_TEST(test_wrap);
    RUN_TEST(test_peek);
    RUN_TEST(test_enqueue_move);
    RUN_TEST(test_emplace);
    RUN_TEST(test_trivial_type);
    RUN_TEST(test_pod_type);
    RUN_TEST(test_non_pod_type);
    RUN_TEST(test_derived_type);

    return UNITY_END();
}

void test_empty()
{
    Queue<uint32_t, 8> uut;

    TEST_ASSERT_EQUAL_UINT32(0, uut.size());
    TEST_ASSERT_EQUAL_UINT32(8, uut.capacity());
    TEST_ASSERT_TRUE(uut.isEmpty());
    TEST_ASSERT_FALSE(uut.isFull());
}

void test_full()
{
    Queue<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(i, uut.size());
        TEST_ASSERT_TRUE(uut.enqueue(i));
    }

    TEST_ASSERT_EQUAL_UINT32(8, uut.size());
    TEST_ASSERT_TRUE(uut.isFull());
}

void test_drain()
{
    Queue<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(i, uut.size());
        TEST_ASSERT_TRUE(uut.enqueue(i));
    }

    TEST_ASSERT(uut.isFull());

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32((size_t)(8-i), uut.size());
        uint32_t item = 0;
        TEST_ASSERT_TRUE(uut.dequeue(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);
    }

    TEST_ASSERT(uut.isEmpty());
}

void test_wrap()
{
    Queue<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 24; i++) {
        TEST_ASSERT_EQUAL_UINT32(0, uut.size());
        TEST_ASSERT_TRUE(uut.enqueue(i));

        uint32_t item = 0;
        TEST_ASSERT_TRUE(uut.dequeue(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);
    }
}

void test_peek()
{
    Queue<uint32_t, 8> uut;

    uint32_t item = 0;
    TEST_ASSERT_FALSE(uut.peek(item));

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(0, uut.size());
        TEST_ASSERT_TRUE(uut.enqueue(i));

        TEST_ASSERT_TRUE(uut.peek(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);

        TEST_ASSERT_TRUE(uut.dequeue(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);
    }
}

void test_enqueue_move()
{
    class Moveable
    {
    public:
        Moveable& operator =(Moveable&& m)
        {
            a = m.a;
            m.a = 0;
            return *this;
        }

        uint32_t a = 0;
    };

    Queue<Moveable, 8> uut;
    Moveable m;

    for (uint8_t i = 0; i < 8; i++) {
        m.a = i;
        TEST_ASSERT_TRUE(uut.enqueue(std::move(m)));
        TEST_ASSERT_EQUAL_UINT32(0, m.a);

        Moveable item;
        TEST_ASSERT_TRUE(uut.dequeue(std::move(item)));
        TEST_ASSERT_EQUAL_UINT32(i, item.a);
    }
}

void test_emplace()
{
    class Stuff
    {
    public:
        Stuff(uint32_t a_, uint8_t b_) : a(a_), b(b_) {};

        uint32_t a;
        uint8_t b;
    };

    Queue<Stuff, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_TRUE(uut.emplace(1234U, i));

        Stuff s(0U,0U);
        TEST_ASSERT_TRUE(uut.dequeue(s));
        TEST_ASSERT_EQUAL_UINT32(1234U, s.a);
        TEST_ASSERT_EQUAL_UINT32(i, s.b);
    }
}

void test_trivial_type()
{
    Queue<uint32_t, 1> uut;

    TEST_ASSERT_TRUE(uut.enqueue(1234U));
    uint32_t out = 0;
    TEST_ASSERT_TRUE(uut.dequeue(out));
    TEST_ASSERT_EQUAL_UINT32(1234U, out);
}

void test_pod_type()
{
    struct Pod
    {
        uint32_t a = 0;
        uint16_t b = 1;
        uint8_t c = 2;
    };

    Queue<Pod, 1> uut;

    Pod in;
    in.a = 1234U;
    in.b = 4321U;
    in.c = 255U;
    TEST_ASSERT_TRUE(uut.enqueue(in));
    Pod out;
    TEST_ASSERT_TRUE(uut.dequeue(out));
    TEST_ASSERT_EQUAL_UINT32(1234U, out.a);
    TEST_ASSERT_EQUAL_UINT32(4321U, out.b);
    TEST_ASSERT_EQUAL_UINT32(255U, out.c);
}

void test_non_pod_type()
{
    struct NonPod
    {
        explicit NonPod(uint32_t a_) : a(a_) {};
        uint32_t a = 0;
    };

    Queue<NonPod, 1> uut;

    NonPod in(1234U);
    TEST_ASSERT_TRUE(uut.enqueue(in));
    NonPod out(0U);
    TEST_ASSERT_TRUE(uut.dequeue(out));
    TEST_ASSERT_EQUAL_UINT32(1234U, out.a);
}

void test_derived_type()
{
    struct Base
    {
        explicit Base(uint32_t a_) : a(a_) {};
        uint32_t a = 0;
    };

    struct Derived : public Base
    {
        explicit Derived(uint32_t a_, uint8_t b_) : Base(a_), b(b_) {};
        uint8_t b = 0;
    };

    Queue<Derived, 1> uut;

    Derived in(1234U, 255U);
    TEST_ASSERT_TRUE(uut.enqueue(in));
    Derived out(0U, 0U);
    TEST_ASSERT_TRUE(uut.dequeue(out));
    TEST_ASSERT_EQUAL_UINT32(1234U, out.a);
    TEST_ASSERT_EQUAL_UINT8(255U, out.b);
}
