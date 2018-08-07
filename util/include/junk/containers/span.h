/**
 * @file   span.h
 * @brief  This file contains the definition of the Span container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-08-06
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef SPAN_H
#define SPAN_H

#include <cstddef>
#include <cstdint>

#include "junk/util/junk_assert.h"

namespace junk {

/**
 * @brief Holds a reference of an array and provides protected access to it.
 *
 * A Span holds a reference to an array (but does not own the array). The Span allows for easy
 * passing and access to an array as well as safe, bounds checked access.
 *
 * The operator[] and at() functions assert that:
 *
 * 1. The array reference is not `nullptr`.
 * 2. The index is within the bounds of the array.
 *
 * @tparam T
 *         The type of item stored in the array.
 */
template <typename T>
class Span {
public:
    /// Default constructor. Sets reference to `nullptr`.
    Span() = default;

    /**
     * @brief Constructor.
     *
     * Uses a C-style array passing to set the array reference.
     *
     * @pre  *ptr* cannot be `nullptr`.
     *
     * @param[in]  ptr
     *             A pointer to the first element in the array.
     * @param[in]  length
     *             The length of the array.
     */
    Span(T* ptr, const size_t length) : m_ptr(ptr), m_len(length)
    {
        JUNK_ASSERT(ptr != nullptr);
    }

    /**
     * @brief Constructor.
     *
     * Takes an array reference.
     *
     * @param[in]  array
     *             A reference to the array to keep track of.
     * @tparam N
     *         The length of the array.
     */
    template <size_t N>
    explicit Span(T (&array)[N]) : Span(&array[0], N)
    {}

    /**
     * @brief Constructor.
     *
     * Uses pointers to the first and last element of the array to define the reference.
     *
     * @pre  *first* cannot be `nullptr`.
     * @pre  *last* cannot be `nullptr`.
     * @pre  *first* must be less than or equal to *last*.
     *
     * @param[in]  first
     *             A pointer to the first element in the array.
     * @param[in]  last
     *             A pointer to the last element in the array.
     */
    Span(T* first, T* last) : Span(first, (size_t)(last - first + 1))
    {
        JUNK_ASSERT(first != nullptr);
        JUNK_ASSERT(last != nullptr);
        JUNK_ASSERT(first <= last);
    }

    /// Default destructor.
    ~Span() = default;

    /**
     * @brief Array subscript operator.
     *
     * @pre  *i* must be strictly less than the length of the array.
     *
     * @param[in]  i
     *             The index of the element to return.
     * @return The element at index *i*.
     */
    T& operator[](const size_t i)
    {
        return at(i);
    }

    /**
     * @brief Const array subscript operator.
     *
     * @pre  *i* must be strictly less than the length of the array.
     *
     * @param[in]  i
     *             The index of the element to return.
     * @return The element at index *i*.
     */
    const T& operator[](const size_t i) const
    {
        return at(i);
    }

    /**
     * @brief Retrieve an element of the array.
     *
     * @pre  *i* must be strictly less than the length of the array.
     *
     * @param[in]  i
     *             The index of the element to return.
     * @return The element at index *i*.
     */
    T& at(const size_t i)
    {
        JUNK_ASSERT(i < m_len);
        return m_ptr[i];
    }

    /**
     * @brief Retrieve an element of the const array.
     *
     * @pre  *i* must be strictly less than the length of the array.
     *
     * @param[in]  i
     *             The index of the element to return.
     * @return The element at index *i*.
     */
    const T& at(const size_t i) const
    {
        JUNK_ASSERT(i < m_len);
        return m_ptr[i];
    }

    /**
     * @brief Get a raw pointer to the referenced array.
     *
     * @warning Modifying or using this pointer directly removes some of the safety guarantees
     *          provided by Span. Do this at your own peril.
     *
     * @return A pointer to the first element of the referenced array.
     */
    T* get()
    {
        return m_ptr;
    }

    /**
     * @overload
     *
     * Provides a const overload of get().
     */
    const T* cget() const
    {
        return m_ptr;
    }

    /**
     * @brief Returns the length of the referenced array.
     *
     * @return The length of the referenced array.
     */
    size_t length() const
    {
        return m_len;
    }

private:
    /// A pointer to the first element of the referenced array.
    T* m_ptr = nullptr;
    /// The length of the referenced array.
    size_t m_len = 0;
};

} // namespace junk

#endif // SPAN_H
