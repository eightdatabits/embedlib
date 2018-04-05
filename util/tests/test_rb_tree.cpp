/**
 * @file      test_rb_tree.cpp
 * @brief     This file contains tests for RbTree.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-03-29
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#include <cstdlib>
#include <chrono>
#include <unordered_map>

#include "unity.h"

#include "junk/util/util.h"
#include "junk/containers/key_pair.h"

#define private public
#define protected public
#include "junk/containers/rb_tree.h"
#undef protected
#undef private

#include <iostream>

using namespace junk;

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, KeyPair<Key,Value> const &pair) {
    return os << '{' << pair.key << ',' << pair.value << '}';
}

template <size_t N, typename T>
void printNode(typename RbTree<N,T>::Node* node)
{
    std::cout << '{' << node->item << ':';
    if (node->color == RbTree<N,T>::Node::Color::kBlack) {
        std::cout << 'B';
    } else {
        std::cout << 'R';
    }
    std::cout << '}' << std::endl;
}

uint32_t g_depth = 0;
template <size_t N, typename T>
void printTree(typename RbTree<N,T>::Node* node)
{
    if ((node->left == nullptr) && (node->right == nullptr)) {
        std::cout << "leaf" << std::endl;
        printNode<N,T>(node);
        return;
    }

    printNode<N,T>(node);

    if (node->left != nullptr) {
        std::cout << "left" << std::endl;
        printTree<N,T>(node->left);
    }

    if (node->right != nullptr) {
        std::cout << "right" << std::endl;
        printTree<N,T>(node->right);
    }
}

template <size_t N, typename T>
uint32_t treeDepth(typename RbTree<N,T>::Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    if ((node->left == nullptr) && (node->right == nullptr)) {
        return 1;
    }

    uint32_t depth = 0;

    if (node->left != nullptr) {
        depth = treeDepth<N,T>(node->left);
    }

    if (node->right != nullptr) {
        depth = util::max(depth,treeDepth<N,T>(node->right));
    }

    return depth + 1;
}

template <size_t N, typename T>
bool checkBlackChildren(typename RbTree<N,T>::Node* node)
{
    if (node == nullptr) {
        return true;
    }

    if (node->color == RbTree<N,T>::Node::Color::kRed) {
        if ((node->left != nullptr) &&
            (node->left->color != RbTree<N,T>::Node::Color::kBlack)) {
            return false;
        }
        if ((node->right != nullptr) &&
            (node->right->color != RbTree<N,T>::Node::Color::kBlack)) {
            return false;
        }
    }

    bool result = true;

    if (node->left != nullptr) {
        result = result && checkBlackChildren<N,T>(node->left);
    }

    if (node->right != nullptr) {
        result = result && checkBlackChildren<N,T>(node->right);
    }

    return result;
}

template <size_t N, typename T>
int32_t checkTraversal(typename RbTree<N,T>::Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    int32_t left_black_depth = 0;
    if (node->left == nullptr) {
        left_black_depth = 1;
    } else {
        left_black_depth = checkTraversal<N,T>(node->left);
    }

    int32_t right_black_depth = 0;
    if (node->right == nullptr) {
        right_black_depth = 1;
    } else {
        right_black_depth = checkTraversal<N,T>(node->right);
    }

    if ((left_black_depth < 0) || (right_black_depth < 0)) {
        return -1;
    }

    if (left_black_depth != right_black_depth) {
        return -1;
    }

    if (node->color == RbTree<N,T>::Node::Color::kBlack) {
        left_black_depth++;
    }

    return left_black_depth;
}

template <size_t N, typename T>
bool checkRbTree(const RbTree<N,T>& tree)
{
    uint32_t tree_depth = treeDepth<N,T>(tree.m_root);
    if (tree_depth == 0) {
        return true;
    }

    if (tree.m_root->color != RbTree<N,T>::Node::Color::kBlack) {
        printTree<N,T>(tree.m_root);
        std::cout << "Root was not black." << std::endl;
        return false;
    }

    if (!checkBlackChildren<N,T>(tree.m_root)) {
        printTree<N,T>(tree.m_root);
        std::cout << "A red node had one or more red children." << std::endl;
        return false;
    }

    int32_t black_depth = checkTraversal<N,T>(tree.m_root);
    if (black_depth < 0) {
        printTree<N,T>(tree.m_root);
        std::cout << "Not all paths have the same black depth." << std::endl;
        return false;
    }

    if (tree_depth > (2 * (uint32_t)black_depth)) {
        printTree<N,T>(tree.m_root);
        std::cout << "Depth > 2*B: B=" << black_depth << ", D=" << tree_depth << std::endl;
        return false;
    }

    return true;
}

void test_default_constructor();
void test_parent_null();
void test_parent();
void test_grandparent_null();
void test_grandparent();
void test_uncle_null();
void test_uncle_left();
void test_uncle_right();
void test_rotate_right0();
void test_rotate_right1();
void test_rotate_right2_right();
void test_rotate_right2_left();
void test_rotate_right3_right();
void test_rotate_right3_left();
void test_rotate_right3_balanced();
void test_rotate_right3_right_left();
void test_rotate_right3_left_right();
void test_rotate_right3_left_right_not_root();
void test_rotate_left0();
void test_rotate_left1();
void test_rotate_left2_right();
void test_rotate_left2_left();
void test_rotate_left3_right();
void test_rotate_left3_left();
void test_rotate_left3_balanced();
void test_rotate_left3_right_left();
void test_rotate_left3_right_left_not_root();
void test_rotate_left3_left_right();
void test_insert_array();
void test_insert_array_oversize();
void test_insert_loop();
void test_insert_move_loop();
void test_search_unknown();
void test_const_search_unknown();
void test_fuzzy_insert_search();

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_default_constructor);
    RUN_TEST(test_parent_null);
    RUN_TEST(test_parent);
    RUN_TEST(test_grandparent_null);
    RUN_TEST(test_grandparent);
    RUN_TEST(test_uncle_null);
    RUN_TEST(test_uncle_left);
    RUN_TEST(test_uncle_right);
    RUN_TEST(test_rotate_right0);
    RUN_TEST(test_rotate_right1);
    RUN_TEST(test_rotate_right2_right);
    RUN_TEST(test_rotate_right2_left);
    RUN_TEST(test_rotate_right3_right);
    RUN_TEST(test_rotate_right3_left);
    RUN_TEST(test_rotate_right3_balanced);
    RUN_TEST(test_rotate_right3_right_left);
    RUN_TEST(test_rotate_right3_left_right);
    RUN_TEST(test_rotate_right3_left_right_not_root);
    RUN_TEST(test_rotate_left0);
    RUN_TEST(test_rotate_left1);
    RUN_TEST(test_rotate_left2_right);
    RUN_TEST(test_rotate_left2_left);
    RUN_TEST(test_rotate_left3_right);
    RUN_TEST(test_rotate_left3_left);
    RUN_TEST(test_rotate_left3_balanced);
    RUN_TEST(test_rotate_left3_right_left);
    RUN_TEST(test_rotate_left3_right_left_not_root);
    RUN_TEST(test_rotate_left3_left_right);
    RUN_TEST(test_insert_array);
    RUN_TEST(test_insert_array_oversize);
    RUN_TEST(test_insert_loop);
    RUN_TEST(test_insert_move_loop);
    RUN_TEST(test_search_unknown);
    RUN_TEST(test_const_search_unknown);
    for (uint32_t i = 0; i < 32U; i++) {
        RUN_TEST(test_fuzzy_insert_search);
    }

    return UNITY_END();
}

// Test Constructors/Destructors ===============================================

void test_default_constructor()
{
    RbTree<8U, int> rb;

    TEST_ASSERT_TRUE(checkRbTree(rb));
    uint32_t depth = treeDepth<8U,int>(rb.m_root);
    TEST_ASSERT_EQUAL_UINT32(0U, depth);
}

// Test parent() ===============================================================

void test_parent_null()
{
    RbTree<8U,int>::Node* result = RbTree<8U,int>::parent(nullptr);
    TEST_ASSERT_NULL(result);
}

void test_parent()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(1);

    a.right = &b;
    b.parent = &a;

    RbTree<8U,int>::Node* result = RbTree<8U,int>::parent(&a);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::parent(&b);
    TEST_ASSERT_EQUAL_PTR(&a, result);
}

// Test grandparent() ==========================================================

void test_grandparent_null()
{
    RbTree<8U,int>::Node* result = RbTree<8U,int>::grandparent(nullptr);
    TEST_ASSERT_NULL(result);
}

void test_grandparent()
{
    RbTree<8U,int>::Node grand(0);
    RbTree<8U,int>::Node parent(1);
    RbTree<8U,int>::Node child(2);

    grand.right = &parent;
    parent.parent = &grand;
    parent.right = &child;
    child.parent = &parent;

    RbTree<8U,int>::Node* result = RbTree<8U,int>::grandparent(&grand);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::grandparent(&parent);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::grandparent(&child);
    TEST_ASSERT_EQUAL_PTR(&grand, result);
}

// Test uncle() ===============================================================

void test_uncle_null()
{
    RbTree<8U,int>::Node* result = RbTree<8U,int>::uncle(nullptr);
    TEST_ASSERT_NULL(result);
}

void test_uncle_left()
{
    RbTree<8U,int>::Node g(0);
    RbTree<8U,int>::Node p(1);
    RbTree<8U,int>::Node c(2);
    RbTree<8U,int>::Node u(-1);

    g.left = &u;
    g.right = &p;
    p.parent = &g;
    u.parent = &g;
    p.right = &c;
    c.parent = &p;

    RbTree<8U,int>::Node* result = RbTree<8U,int>::uncle(&g);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::uncle(&p);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::uncle(&c);
    TEST_ASSERT_EQUAL_PTR(&u, result);
}

void test_uncle_right()
{
    RbTree<8U,int>::Node g(0);
    RbTree<8U,int>::Node p(-1);
    RbTree<8U,int>::Node c(-2);
    RbTree<8U,int>::Node u(1);

    g.left = &p;
    g.right = &u;
    p.parent = &g;
    u.parent = &g;
    p.left = &c;
    c.parent = &p;

    RbTree<8U,int>::Node* result = RbTree<8U,int>::uncle(&g);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::uncle(&p);
    TEST_ASSERT_NULL(result);
    result = RbTree<8U,int>::uncle(&c);
    TEST_ASSERT_EQUAL_PTR(&u, result);
}

//  Test rotateRight() ========================================================

void test_rotate_right0()
{
    RbTree<8U,int>::rotateRight(nullptr);
}

void test_rotate_right1()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::rotateRight(&a);

    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_NULL(a.parent);
}

void test_rotate_right2_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(1);

    a.right = &b;
    b.parent = &a;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&b, a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
}

void test_rotate_right2_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);

    a.left = &b;
    b.parent = &a;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&a, b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
}

void test_rotate_right3_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(1);
    RbTree<8U,int>::Node c(2);

    a.right = &b;
    b.parent = &a;
    b.right = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&b, a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&c, b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
}

void test_rotate_right3_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);
    RbTree<8U,int>::Node c(-2);

    a.left = &b;
    b.parent = &a;
    b.left = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_EQUAL_PTR(&c, b.left);
    TEST_ASSERT_EQUAL_PTR(&a, b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
}

void test_rotate_right3_balanced()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);
    RbTree<8U,int>::Node c(1);

    a.left = &b;
    b.parent = &a;
    a.right = &c;
    c.parent = &a;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&a, b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&c, a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&a, c.parent);
}

void test_rotate_right3_right_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(2);
    RbTree<8U,int>::Node c(1);

    a.right = &b;
    b.parent = &a;
    b.left = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&b, a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_EQUAL_PTR(&c, b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
}

void test_rotate_right3_left_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-2);
    RbTree<8U,int>::Node c(-1);

    a.left = &b;
    b.parent = &a;
    b.right = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&a, b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_EQUAL_PTR(&c, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&a, c.parent);
}

void test_rotate_right3_left_right_not_root()
{
    RbTree<8U,int>::Node r(0);
    RbTree<8U,int>::Node a(-1);
    RbTree<8U,int>::Node b(-3);
    RbTree<8U,int>::Node c(-2);

    r.left = &a;
    a.parent = &r;
    a.left = &b;
    b.parent = &a;
    b.right = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateRight(&a);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&a, b.right);
    TEST_ASSERT_EQUAL_PTR(&r, b.parent);
    TEST_ASSERT_EQUAL_PTR(&c, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&a, c.parent);
}

// Test rotateLeft() ==============================================================

void test_rotate_left0()
{
    RbTree<8U,int>::rotateLeft(nullptr);
}

void test_rotate_left1()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::rotateLeft(&a);

    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_NULL(a.parent);
}

void test_rotate_left2_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(1);

    a.right = &b;
    b.parent = &a;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&a, b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
}

void test_rotate_left2_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);

    a.left = &b;
    b.parent = &a;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&b, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
}

void test_rotate_left3_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(1);
    RbTree<8U,int>::Node c(2);

    a.right = &b;
    b.parent = &a;
    b.right = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&a, b.left);
    TEST_ASSERT_EQUAL_PTR(&c, b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
}

void test_rotate_left3_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);
    RbTree<8U,int>::Node c(-2);

    a.left = &b;
    b.parent = &a;
    b.left = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&b, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_EQUAL_PTR(&c, b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
}

void test_rotate_left3_balanced()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-1);
    RbTree<8U,int>::Node c(1);

    a.left = &b;
    b.parent = &a;
    a.right = &c;
    c.parent = &a;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&a, c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_NULL(c.parent);
    TEST_ASSERT_EQUAL_PTR(&b, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_EQUAL_PTR(&c, a.parent);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
}

void test_rotate_left3_right_left()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(2);
    RbTree<8U,int>::Node c(1);

    a.right = &b;
    b.parent = &a;
    b.left = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&a, b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_NULL(b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&c, a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&a, c.parent);
}

void test_rotate_left3_right_left_not_root()
{
    RbTree<8U,int>::Node r(0);
    RbTree<8U,int>::Node a(1);
    RbTree<8U,int>::Node b(3);
    RbTree<8U,int>::Node c(2);

    r.right = &a;
    a.parent = &r;
    a.right = &b;
    b.parent = &a;
    b.left = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&a, b.left);
    TEST_ASSERT_NULL(b.right);
    TEST_ASSERT_EQUAL_PTR(&r, b.parent);
    TEST_ASSERT_NULL(a.left);
    TEST_ASSERT_EQUAL_PTR(&c, a.right);
    TEST_ASSERT_EQUAL_PTR(&b, a.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&a, c.parent);
}

void test_rotate_left3_left_right()
{
    RbTree<8U,int>::Node a(0);
    RbTree<8U,int>::Node b(-2);
    RbTree<8U,int>::Node c(-1);

    a.left = &b;
    b.parent = &a;
    b.right = &c;
    c.parent = &b;

    RbTree<8U,int>::rotateLeft(&a);
    TEST_ASSERT_EQUAL_PTR(&b, a.left);
    TEST_ASSERT_NULL(a.right);
    TEST_ASSERT_NULL(a.parent);
    TEST_ASSERT_NULL(b.left);
    TEST_ASSERT_EQUAL_PTR(&c, b.right);
    TEST_ASSERT_EQUAL_PTR(&a, b.parent);
    TEST_ASSERT_NULL(c.left);
    TEST_ASSERT_NULL(c.right);
    TEST_ASSERT_EQUAL_PTR(&b, c.parent);
}

// Test Insert Array ==============================================================

void test_insert_array()
{
    RbTree<16U,int> rb;
    int items[16] = {0,
                     1,
                     2,
                     3,
                     4,
                     5,
                     6,
                     7,
                     8,
                     9,
                     10,
                     11,
                     12,
                     13,
                     14,
                     15};
    TEST_ASSERT_TRUE(rb.insert(items));

    TEST_ASSERT_TRUE(checkRbTree(rb));

    for (int i = 0; i < 16; i++) {
        int* value = rb.search(i);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT32(i, *value);
    }
}

void test_insert_array_oversize()
{
    RbTree<12U,int> rb;
    int items[16] = {0,
                     1,
                     2,
                     3,
                     4,
                     5,
                     6,
                     7,
                     8,
                     9,
                     10,
                     11,
                     12,
                     13,
                     14,
                     15};
    TEST_ASSERT_TRUE(rb.insert(items));

    TEST_ASSERT_TRUE(checkRbTree(rb));

    for (int i = 0; i < 12; i++) {
        int* value = rb.search(i);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT32(i, *value);
    }
}

void test_insert_loop()
{
    RbTree<256U,int> rb;
    int item;

    for (int i = 0; i < 256; i++) {
        item = i;
        TEST_ASSERT_TRUE(rb.insert(item));
        TEST_ASSERT_TRUE(checkRbTree(rb));
    }

    for (int i = 0; i < 256; i++) {
        int* value = rb.search(i);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT32(i, *value);
    }
}

void test_insert_move_loop()
{
    RbTree<256U,int> rb;
    int item;

    for (int i = 0; i < 256; i++) {
        item = i;
        TEST_ASSERT_TRUE(rb.insert(std::move(item)));
        TEST_ASSERT_TRUE(checkRbTree(rb));
    }

    for (int i = 0; i < 256; i++) {
        int* value = rb.search(i);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT32(i, *value);
    }
}

void test_search_unknown()
{
    RbTree<256U,int> rb;
    int item;

    // Fill tree just to ensure there is something to search
    for (int i = 0; i < 256; i++) {
        item = i;
        TEST_ASSERT_TRUE(rb.insert(std::move(item)));
        TEST_ASSERT_TRUE(checkRbTree(rb));
    }

    for (int i = 256; i < 1024; i++) {
        int* value = rb.search(i);
        TEST_ASSERT_NULL(value);
    }
}

void test_const_search_unknown()
{
    RbTree<256U,int> rb;
    int item;

    // Fill tree just to ensure there is something to search
    for (int i = 0; i < 256; i++) {
        item = i;
        TEST_ASSERT_TRUE(rb.insert(std::move(item)));
        TEST_ASSERT_TRUE(checkRbTree(rb));
    }

    for (int i = 256; i < 1024; i++) {
        const int* value = static_cast<const RbTree<256U,int>>(rb).search(i);
        TEST_ASSERT_NULL(value);
    }
}

void test_fuzzy_insert_search()
{
    RbTree<4096U,KeyPair<uint32_t,uint32_t>> rb;
    KeyPair<uint32_t,uint32_t> pair;
    std::unordered_map<uint32_t,uint32_t> map;

#ifdef FUZZ_SEED
    uint32_t seed = FUZZ_SEED;
#else
    uint32_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
#endif
    std::cout << "Fuzz seed: " << seed << std::endl;
    srand(seed);

    // Fill tree with random numbers
    for (uint32_t i = 0; i < 4096U; i++) {
        // Ensure we don't get duplicates
        do {
            pair.key = static_cast<uint16_t>(rand());
            pair.value = i;
        } while(map.find(pair.key) != map.end());

        map.insert({pair.key, pair.value});
        TEST_ASSERT_TRUE(rb.insert(pair));
        TEST_ASSERT_TRUE(checkRbTree(rb));
    }

    uint32_t hits = 0;
    uint32_t misses = 0;

    // Search for random values in the tree
    for (uint32_t i = 0; i < 65536U; i++) {
        uint32_t key = static_cast<uint16_t>(rand());
        KeyPair<uint32_t,uint32_t>* result = rb.search(key);
        if (map.find(key) != map.end()) {
            if (result == nullptr) {
                std::cout << key << std::endl;
                printTree<4096U,KeyPair<uint32_t,uint32_t>>(rb.m_root);
            }
            TEST_ASSERT_NOT_NULL(result);
            TEST_ASSERT_EQUAL_UINT32(map.find(key)->second, result->value);
            hits++;
        } else {
            misses++;
            TEST_ASSERT_NULL(result);
        }
    }

    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: " << misses << std::endl;
}
