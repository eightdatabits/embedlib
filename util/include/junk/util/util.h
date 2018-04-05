/**
 * @file   util.h
 * @brief  This file contains random utilities.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-03-21
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef UTIL_H
#define UTIL_H

#include <cstddef>
#include <cstdint>

namespace junk {
namespace util {

template <typename T>
constexpr T& max(T& a, T& b)
{
    // Always prefer to return a in the case of equality
    return !(a < b) ? a : b;
}

template <typename T>
constexpr const T& max(const T& a, const T& b)
{
    // Always prefer to return a in the case of equality
    return !(a < b) ? a : b;
}

template <typename T>
constexpr T& min(T& a, T& b)
{
    // Always prefer to return a in the case of equality
    return (a < b) ? a : b;
}

template <typename T>
constexpr const T& min(const T& a, const T& b)
{
    // Always prefer to return a in the case of equality
    return (a < b) ? a : b;
}

} // namespace util
} // namespace junk

#endif // UTIL_H
