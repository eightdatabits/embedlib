/**
 * @file   queue.h
 * @brief  This file contains the definition of the Queue container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-02-01
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <cstdint>
#include <new>
#include <utility>

#include "embedlib/common/emb_assert.h"

namespace emb {

template <class T, size_t S>
class Queue
{
public:
    Queue() = default;
    ~Queue() = default;

    bool enqueue(const T& item)
    {
        bool success = false;

        if (!isFull()) {
            *reinterpret_cast<T*>(&m_storage[m_write_index]) = item;
            m_write_index++;
            if (m_write_index >= S) {
                m_write_index = 0;
            }
            m_size++;
            success = true;
        }

        return success;
    }

    bool enqueue(T&& item)
    {
        bool success = false;

        if (!isFull()) {
            *reinterpret_cast<T*>(&m_storage[m_write_index]) = std::move(item);
            m_write_index++;
            if (m_write_index >= S) {
                m_write_index = 0;
            }
            m_size++;
            success = true;
        }

        return success;
    };

    bool enqueue(const T&& item)
    {
        bool success = false;

        if (!isFull()) {
            *reinterpret_cast<T*>(&m_storage[m_write_index]) = std::move(item);
            m_write_index++;
            if (m_write_index >= S) {
                m_write_index = 0;
            }
            m_size++;
            success = true;
        }

        return success;
    };

    template <typename ... Args>
    bool emplace(Args&&... args)
    {
        bool success = false;

        if (!isFull()) {
            new (reinterpret_cast<T*>(&m_storage[m_write_index])) T(std::forward<Args>(args)...);
            m_write_index++;
            if (m_write_index >= S) {
                m_write_index = 0;
            }
            m_size++;
            success = true;
        }

        return success;
    };

    bool dequeue(T& item)
    {
        bool success = false;

        if (!isEmpty()) {
            item = *reinterpret_cast<T*>(&m_storage[m_read_index]);
            reinterpret_cast<T*>(&m_storage[m_read_index])->~T();
            m_read_index++;
            if (m_read_index >= S) {
                m_read_index = 0;
            }
            m_size--;
            success = true;
        }

        return success;
    };

    bool dequeue(T&& item)
    {
        bool success = false;

        if (!isEmpty()) {
            item = std::move(*reinterpret_cast<T*>(&m_storage[m_read_index]));
            reinterpret_cast<T*>(&m_storage[m_read_index])->~T();
            m_read_index++;
            if (m_read_index >= S) {
                m_read_index = 0;
            }
            m_size--;
            success = true;
        }

        return success;
    };

    bool peek(T& item) const
    {
        bool success = false;

        if (!isEmpty()) {
            item = *reinterpret_cast<const T*>(&m_storage[m_read_index]);
            success = true;
        }

        return success;
    };

    bool isFull() const
    {
        return (m_size >= S);
    };

    bool isEmpty() const
    {
        return (m_size == 0);
    };

    size_t size() const
    {
        return m_size;
    };

    size_t capacity() const
    {
        return S;
    };

private:
    struct alignas(T) StorageHelper {
        uint8_t mem[sizeof(T)];
    };

    size_t m_read_index = 0;
    size_t m_write_index = 0;
    size_t m_size = 0;

    StorageHelper m_storage[S] {};
};

} // namespace emb

#endif // QUEUE_H
