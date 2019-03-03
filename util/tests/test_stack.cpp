/**
 * @file      test_stack.cpp
 * @brief     This file contains tests for Stack.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2019-02-23
 * @copyright Copyright (c) 2019 Liam Bucci. See included LICENSE file.
 */

#include "unity.h"

#include "junk/containers/stack.h"

using namespace junk;

void test_empty();
void test_full();
void test_drain();
void test_overwrite();
void test_peek();
void test_push_move();
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
    RUN_TEST(test_overwrite);
    RUN_TEST(test_peek);
    RUN_TEST(test_push_move);
    RUN_TEST(test_emplace);
    RUN_TEST(test_trivial_type);
    RUN_TEST(test_pod_type);
    RUN_TEST(test_non_pod_type);
    RUN_TEST(test_derived_type);

    return UNITY_END();
}

void test_empty()
{
    Stack<uint32_t, 8> uut;

    TEST_ASSERT_EQUAL_UINT32(0, uut.size());
    TEST_ASSERT_EQUAL_UINT32(8, uut.capacity());
    TEST_ASSERT_TRUE(uut.isEmpty());
    TEST_ASSERT_FALSE(uut.isFull());
}

void test_full()
{
    Stack<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(i, uut.size());
        TEST_ASSERT_TRUE(uut.push(i));
    }

    TEST_ASSERT_EQUAL_UINT32(8, uut.size());
    TEST_ASSERT_TRUE(uut.isFull());
}

void test_drain()
{
    Stack<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(i, uut.size());
        TEST_ASSERT_TRUE(uut.push(i));
    }

    TEST_ASSERT(uut.isFull());

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32((size_t)(8-i), uut.size());
        uint32_t item = 0;
        TEST_ASSERT_TRUE(uut.pop(item));
        TEST_ASSERT_EQUAL_UINT32(8-i-1, item);
    }

    TEST_ASSERT(uut.isEmpty());
}

void test_overwrite()
{
    Stack<uint32_t, 8> uut;

    for (uint8_t i = 0; i < 24; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            TEST_ASSERT_EQUAL_UINT32(j, uut.size());
            TEST_ASSERT_TRUE(uut.push(j));
        }

        for (uint8_t j = 0; j < 8; j++) {
            uint32_t item = 0;
            TEST_ASSERT_TRUE(uut.pop(item));
            TEST_ASSERT_EQUAL_UINT32(8-j-1, item);
        }
    }
}

void test_peek()
{
    Stack<uint32_t, 8> uut;

    uint32_t item = 0;
    TEST_ASSERT_FALSE(uut.peek(item));

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT32(0, uut.size());
        TEST_ASSERT_TRUE(uut.push(i));

        TEST_ASSERT_TRUE(uut.peek(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);

        TEST_ASSERT_TRUE(uut.pop(item));
        TEST_ASSERT_EQUAL_UINT32(i, item);
    }
}

void test_push_move()
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

    Stack<Moveable, 8> uut;
    Moveable m;

    for (uint8_t i = 0; i < 8; i++) {
        m.a = i;
        TEST_ASSERT_TRUE(uut.push(std::move(m)));
        TEST_ASSERT_EQUAL_UINT32(0, m.a);

        Moveable item;
        TEST_ASSERT_TRUE(uut.pop(std::move(item)));
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

    Stack<Stuff, 8> uut;

    for (uint8_t i = 0; i < 8; i++) {
        TEST_ASSERT_TRUE(uut.emplace(1234U, i));

        Stuff s(0U,0U);
        TEST_ASSERT_TRUE(uut.pop(s));
        TEST_ASSERT_EQUAL_UINT32(1234U, s.a);
        TEST_ASSERT_EQUAL_UINT32(i, s.b);
    }
}

void test_trivial_type()
{
    Stack<uint32_t, 1> uut;

    TEST_ASSERT_TRUE(uut.push(1234U));
    uint32_t out = 0;
    TEST_ASSERT_TRUE(uut.pop(out));
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

    Stack<Pod, 1> uut;

    Pod in;
    in.a = 1234U;
    in.b = 4321U;
    in.c = 255U;
    TEST_ASSERT_TRUE(uut.push(in));
    Pod out;
    TEST_ASSERT_TRUE(uut.pop(out));
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

    Stack<NonPod, 1> uut;

    NonPod in(1234U);
    TEST_ASSERT_TRUE(uut.push(in));
    NonPod out(0U);
    TEST_ASSERT_TRUE(uut.pop(out));
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

    Stack<Derived, 1> uut;

    Derived in(1234U, 255U);
    TEST_ASSERT_TRUE(uut.push(in));
    Derived out(0U, 0U);
    TEST_ASSERT_TRUE(uut.pop(out));
    TEST_ASSERT_EQUAL_UINT32(1234U, out.a);
    TEST_ASSERT_EQUAL_UINT8(255U, out.b);
}
