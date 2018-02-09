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

#include "junk/util/junk_assert.h"

namespace junk {

/**
 * @brief Queue container class.
 *
 * This class is a container which acts as a FIFO circular buffer. It can be used with any type
 * as long as the type is either copyable or movable.
 *
 * @tparam T
 *         The type stored by this container.
 * @tparam S
 *         The maximum number of items that may be stored in this container.
 */
template <class T, size_t S>
class Queue
{
public:
    Queue() = default;

    /**
     * @brief Destructor for Queue container.
     *
     * The destructor ensures all remaining internal items are destructed.
     */
    ~Queue()
    {
        while (!isEmpty()) {
            reinterpret_cast<T*>(&m_storage[m_read_index])->~T();
            m_read_index++;
            if (m_read_index >= S) {
                m_read_index = 0;
            }
            m_size--;
        }
    }

    /**
     * @brief Enqueue a given item.
     *
     * Enqueues the given item at the back of the queue. The type of *T* must be copyable.
     *
     * @param[in]  item
     *             The item to store in the queue.
     * @return A boolean:
     *         - `true`:  The item was stored successfully in the queue.
     *         - `false`: The queue was full.
     */
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

    /**
     * @brief Enqueue a given item.
     *
     * Enqueues the given item at the back of the queue. The type of *T* must be movable.
     *
     * @param[in]  item
     *             The item to store in the queue.
     * @return A boolean:
     *         - `true`:  The item was moved successfully into the queue.
     *         - `false`: The queue was full.
     */
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

    /**
     * @brief Enqueue a given item.
     *
     * @overload
     *
     * @param[in]  item
     *             The item to store in the queue.
     * @return A boolean:
     *         - `true`:  The item was moved successfully into the queue.
     *         - `false`: The queue was full.
     */
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

    /**
     * @brief Emplace an item on the back of the queue.
     *
     * Constructs an object directly on the back of the queue. The item is constructed in place.
     *
     * @param[in]  args
     *             The parameter pack of template arguments that will be forwarded to the type *T*
     *             constructor.
     * @return A boolean:
     *         - `true`:  The item was emplaced on the back of the queue.
     *         - `false`: The queue was full.
     */
    template <typename ... Args>
    bool emplace(Args&&... args)
    {
        bool success = false;

        if (!isFull()) {
            // Construct the item on the queue
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

    /**
     * @brief Retrieve the oldest item from the queue.
     *
     * Retrieves the oldest item from the queue (the item at the front). The item is copied out and
     * then removed from the queue.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The queue was empty.
     */
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

    /**
     * @brief Retrieve the oldest item from the queue.
     *
     * Retrieves the oldest item from the queue (the item at the front). The item is moved into
     * *item*.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The queue was empty.
     */
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

    /**
     * @brief Peek at the next item in the queue.
     *
     * Retrieve a copy of the next item in the queue without removing it from the queue.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The queue was empty.
     */
    bool peek(T& item) const
    {
        bool success = false;

        if (!isEmpty()) {
            item = *reinterpret_cast<const T*>(&m_storage[m_read_index]);
            success = true;
        }

        return success;
    };

    /**
     * @brief Check if the queue is full.
     *
     * @return A boolean:
     *         - `true`:  The queue is full.
     *         - `false`: The queue is not full.
     */
    bool isFull() const
    {
        return (m_size >= S);
    };

    /**
     * @brief Check if the queue is empty.
     *
     * @return A boolean:
     *         - `true`:  The queue is empty.
     *         - `false`: The queue is not empty.
     */
    bool isEmpty() const
    {
        return (m_size == 0);
    };

    /**
     * @brief Get the current number of items in the queue.
     *
     * @return The current number of items in the queue.
     */
    size_t size() const
    {
        return m_size;
    };

    /**
     * @brief Get the maximum number of items that can be stored by the queue.
     *
     * @return The maximum number of items that can be stored by the queue.
     */
    size_t capacity() const
    {
        return S;
    };

private:
    /**
     * @brief A storage container which simulates the type *T*.
     *
     * Each StorageHelper instance has the same alignment and storage requirements as an object of
     * type *T*.
     */
    struct alignas(T) StorageHelper {
        uint8_t mem[sizeof(T)];
    };

    /// The index of the next item to read out (dequeue).
    size_t m_read_index = 0;
    /// The index of the next available write slot (enqueue).
    size_t m_write_index = 0;
    /// The current number of items in the queue.
    size_t m_size = 0;

    /// The actual storage for the queue.
    StorageHelper m_storage[S] {};
};

} // namespace junk

#endif // QUEUE_H
