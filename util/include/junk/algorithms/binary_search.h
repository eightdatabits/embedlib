/**
 * @file   binary_search.h
 * @brief  This file contains the definition of the binarySearch algorithm.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-01-31
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <cstddef>

namespace junk {
namespace algorithms {


/**
 * @brief Perform binary search on an array.
 *
 * Search the given array of type T items for the given item *match*. Returns a pointer to the
 * first matching item found in the array. If no match is found returns a `nullptr`. If multiple
 * items match in the array only the first found is returned, no more searching is done after the
 * first match.
 *
 * @pre The given array must be sorted from lowest (at zero index) to highest (at `length-1` index).
 * @pre The type T must be LessThanComparable (the `operator<()` must be defined).
 *
 * @tparam     T
 *             The type stored in the array to be searched.
 * @param[in]  array
 *             A pointer to the array to be searched.
 * @param[in]  length
 *             The length of the array to be searched.
 * @param[in]  match
 *             The item to find within the array.
 * @return A pointer to the item found if one was found. If no item is found a `nullptr`.
 */
template <typename T>
T* binarySearch(T* const array, const size_t length, const T& match)
{
    if (array == nullptr) {
        return nullptr;
    }

    size_t high_index = length;
    size_t low_index = 0;
    size_t index = length / 2;

    while (low_index != high_index) {
        if (array[index] == match) {
            return &array[index];
        }

        if (array[index] < match) {
            low_index = index;
            index = (high_index + index + 1) / 2;
        } else {
            high_index = index;
            index = (low_index + index) / 2;
        }
    }

    // Above while loop doesn't check the last item (when low_index == high_index)
    if (array[index] == match) {
        return &array[index];
    } else {
        return nullptr;
    }
}

/**
 * @brief Perform binary search on an array.
 *
 * @overload T* binarySearch(T* const array, const size_t length, const T& match)
 *
 * @tparam    T
 *            The type stored in the array to be searched.
 * @tparam    N
 *            The size of the array.
 * @param[in] array
 *            The array of items to search.
 * @param[in] match
 *            The item to look for in the array.
 *
 * @return A pointer to the item in the array if a match was found, otherwise `nullptr`.
 */
template <typename T, size_t N>
T* binarySearch(T (&array)[N], const T& match)
{
    return binarySearch(static_cast<T*>(&array[0]), N, match);
}

/**
 * @brief Perform binary search on an array.
 *
 * @overload T* binarySearch(T* const array, const size_t length, const T& match)
 *
 * Uses a provided predicate instead of `operator <` and `operator ==` when comparing items. Compare
 * predicate must have a signature similar to: `int comp(const T& a, const T& b)`.
 * Where the return values follow:
 * * `0` if `a == b`
 * * A negative number if `a < b`
 * * A positive number if `a > b`.
 *
 * @tparam     T
 *             The type stored in the array.
 * @tparam     Compare
 *             The type of the predicate used to compare two items.
 * @param[in]  array
 *             The array of items to search.
 * @param[in]  length
 *             The length of the array to be searched.
 * @param[in]  match
 *             The item to find within the array.
 * @param[in]  comp
 *             The predicate to use to compare two items.
 *
 * @return A pointer to the item found if one is found. Otherwise, a `nullptr`.
 */
template <typename T, typename Compare>
T* binarySearch(T* const array, const size_t length, const T& match, Compare comp)
{
    if (array == nullptr) {
        return nullptr;
    }

    size_t high_index = length;
    size_t low_index = 0;
    size_t index = length / 2;

    while (low_index != high_index) {
        // Check for equality
        if (comp(array[index], match) == 0) {
            return &array[index];
        }

        // Check if array[index] < match
        if (comp(array[index], match) < 0) {
            low_index = index;
            index = (high_index + index + 1) / 2;
        } else {
            high_index = index;
            index = (low_index + index) / 2;
        }
    }

    // Above while loop doesn't check the last item (when low_index == high_index)
    if (comp(array[index], match) == 0) {
        return &array[index];
    } else {
        return nullptr;
    }
}

/**
 * @brief Perform binary search on an array.
 *
 * @overload T* binarySearch(T* const array, const size_t length, const T& match, Compare comp)
 *
 * @tparam     T
 *             The type stored in the array.
 * @tparam     N
 *             The size of the array.
 * @tparam     Compare
 *             The type of the predicate used to compare two items.
 * @param[in]  array
 *             The array of items to search.
 * @param[in]  match
 *             The item to find within the array.
 * @param[in]  comp
 *             The predicate to use to compare two items.
 *
 * @return A pointer to the item found if one is found. Otherwise, a `nullptr`.
 */
template <typename T, size_t N, typename Compare>
T* binarySearch(T (&array)[N], const T& match, Compare comp)
{
    return binarySearch(&array[0], N, match, comp);
}

} // namespace algorithms
} // namespace junk

#endif // SEARCH_H