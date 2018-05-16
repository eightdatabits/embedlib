/**
 * @file   pair.h
 * @brief  This file contains the definition of the Pair container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-03-30
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef PAIR_H
#define PAIR_H


namespace junk {

template <typename A, typename B>
struct Pair {
    Pair(const A& a, const B& b) : a(a), b(b) {};

    A a;
    B b;
};

template <typename A, typename B>
constexpr bool operator ==(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return (p1.a == p2.a) && (p1.b == p2.b);
}

template <typename A, typename B>
constexpr bool operator !=(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return !(p1 == p2);
}

template <typename A, typename B>
constexpr bool operator <(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return (p1.a < p2.a) && (p1.b < p2.b);
}

template <typename A, typename B>
constexpr bool operator >(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return !(p1 < p2) && (p1 != p2);
}

template <typename A, typename B>
constexpr bool operator <=(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return (p1 < p2) || (p1 == p2);
}

template <typename A, typename B>
constexpr bool operator >=(const Pair<A,B>& p1, const Pair<A,B>& p2)
{
    return (p1 > p2) || (p1 == p2);
}


template <typename A, typename B>
constexpr bool operator ==(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return (p1.a == p2.a) && (p1.b == p2.b);
}

template <typename A, typename B>
constexpr bool operator !=(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return !(p1 == p2);
}

template <typename A, typename B>
constexpr bool operator <(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return (p1.a < p2.a) && (p1.b < p2.b);
}

template <typename A, typename B>
constexpr bool operator >(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return !(p1 < p2) && (p1 != p2);
}

template <typename A, typename B>
constexpr bool operator <=(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return (p1 < p2) || (p1 == p2);
}

template <typename A, typename B>
constexpr bool operator >=(const Pair<A,B>&& p1, const Pair<A,B>&& p2)
{
    return (p1 > p2) || (p1 == p2);
}

} // namespace junk

#endif // PAIR_H
