/**
 * @file   key_pair.h
 * @brief  This file contains the definition of the KeyPair container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-03-30
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef KEY_PAIR_H
#define KEY_PAIR_H


namespace junk {

template <typename Key, typename Value>
struct KeyPair {
    constexpr KeyPair() = default;
    constexpr KeyPair(const Key& k, const Value& v) : key(k), value(v) {};

    Key key;
    Value value;
};

template <typename Key, typename Value>
constexpr bool operator ==(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key == p2.key);
}

template <typename Key, typename Value>
constexpr bool operator !=(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key != p2.key);
}

template <typename Key, typename Value>
constexpr bool operator <(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key < p2.key);
}

template <typename Key, typename Value>
constexpr bool operator >(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key > p2.key);
}

template <typename Key, typename Value>
constexpr bool operator <=(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key <= p2.key);
}

template <typename Key, typename Value>
constexpr bool operator >=(const KeyPair<Key,Value>& p1, const KeyPair<Key,Value>& p2)
{
    return (p1.key >= p2.key);
}


template <typename Key, typename Value>
constexpr bool operator ==(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1.key == p2.key);
}

template <typename Key, typename Value>
constexpr bool operator !=(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1 != p2);
}

template <typename Key, typename Value>
constexpr bool operator <(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1.key < p2.key);
}

template <typename Key, typename Value>
constexpr bool operator >(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1.key > p2.key);
}

template <typename Key, typename Value>
constexpr bool operator <=(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1.key <= p2.key);
}

template <typename Key, typename Value>
constexpr bool operator >=(const KeyPair<Key,Value>&& p1, const KeyPair<Key,Value>&& p2)
{
    return (p1.key >= p2.key);
}


template <typename Key, typename Value>
constexpr bool operator ==(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key == key);
}

template <typename Key, typename Value>
constexpr bool operator !=(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key != key);
}

template <typename Key, typename Value>
constexpr bool operator <(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key < key);
}

template <typename Key, typename Value>
constexpr bool operator >(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key > key);
}

template <typename Key, typename Value>
constexpr bool operator <=(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key <= key);
}

template <typename Key, typename Value>
constexpr bool operator >=(const KeyPair<Key,Value>& p, const Key& key)
{
    return (p.key >= key);
}


template <typename Key, typename Value>
constexpr bool operator ==(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key == p.key);
}

template <typename Key, typename Value>
constexpr bool operator !=(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key != p.key);
}

template <typename Key, typename Value>
constexpr bool operator <(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key < p.key);
}

template <typename Key, typename Value>
constexpr bool operator >(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key > p.key);
}

template <typename Key, typename Value>
constexpr bool operator <=(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key <= p.key);
}

template <typename Key, typename Value>
constexpr bool operator >=(const Key& key, const KeyPair<Key,Value>& p)
{
    return (key >= p.key);
}

} // namespace junk

#endif // KEY_PAIR_H
