/**
 * @file   stack.h
 * @brief  This file contains the definition of the Stack container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2019-02-23
 * @copyright Copyright (c) 2019 Liam Bucci. See included LICENSE file.
 */

#ifndef STACK_H
#define STACK_H

#include <cstdint>
#include <new>
#include <utility>

namespace junk {

/**
 * @brief Stack container class.
 *
 * This class is a container which acts as a FILO stack. It can be used with any type
 * as long as the type is either copyable or movable.
 *
 * @tparam T
 *         The type stored by this container.
 * @tparam Capacity
 *         The maximum number of items that may be stored in this container.
 */
template <class T, size_t Capacity>
class Stack
{
public:
    Stack() = default;

    /**
     * @brief Destructor for Stack container.
     *
     * The destructor ensures all remaining internal items are destructed.
     */
    ~Stack()
    {
        while (pop()) {}
    }

    /**
     * @brief Push the given item onto the stack (by copying).
     *
     * Pushes the given item to the top of the stack. The type of *T* must be copyable.
     *
     * @param[in]  item
     *             The item to store in the stack.
     * @return A boolean:
     *         - `true`:  The item was stored successfully on the stack.
     *         - `false`: The stack was full.
     */
    bool push(const T& item)
    {
        bool success = false;

        if (!isFull()) {
            *reinterpret_cast<T*>(&m_storage[m_size]) = item;
            m_size++;
            success = true;
        }

        return success;
    }

    /**
     * @brief Push a given item onto the stack (by moving).
     *
     * Push the given item to the top of the stack. The type of *T* must be movable.
     *
     * @param[in]  item
     *             The item to store on the stack.
     * @return A boolean:
     *         - `true`:  The item was moved successfully on the stack.
     *         - `false`: The stack was full.
     */
    bool push(T&& item)
    {
        bool success = false;

        if (!isFull()) {
            *reinterpret_cast<T*>(&m_storage[m_size]) = std::move(item);
            m_size++;
            success = true;
        }

        return success;
    };

    /**
     * @brief Emplace an item on the top of the stack.
     *
     * Constructs an object directly on the top of the stack. The item is constructed in place.
     *
     * @param[in]  args
     *             The parameter pack of template arguments that will be forwarded to the type *T*
     *             constructor.
     * @return A boolean:
     *         - `true`:  The item was emplaced on the top of the stack.
     *         - `false`: The queue was full.
     */
    template <typename ... Args>
    bool emplace(Args&&... args)
    {
        bool success = false;

        if (!isFull()) {
            // Construct the item on the stack
            new (reinterpret_cast<T*>(&m_storage[m_size])) T(std::forward<Args>(args)...);
            m_size++;
            success = true;
        }

        return success;
    };

    /**
     * @brief Retrieve the item from the top of the stack (by copying).
     *
     * Retrieves the top-most item from the stack (the newest item). The item is copied out and
     * then removed from the stack.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The stack was empty.
     */
    bool pop(T& item)
    {
        bool success = false;

        if (!isEmpty()) {
            m_size--;
            item = *reinterpret_cast<T*>(&m_storage[m_size]);
            reinterpret_cast<T*>(&m_storage[m_size])->~T();
            success = true;
        }

        return success;
    };

    /**
     * @brief Retrieve the item from the top of the stack (by moving).
     *
     * Retrieves the top-most item from the stack (the newest item). The item is moved into
     * *item*.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The stack was empty.
     */
    bool pop(T&& item)
    {
        bool success = false;

        if (!isEmpty()) {
            m_size--;
            item = std::move(*reinterpret_cast<T*>(&m_storage[m_size]));
            reinterpret_cast<T*>(&m_storage[m_size])->~T();
            success = true;
        }

        return success;
    };

    /**
     * @brief Remove the top item from the stack.
     *
     * Removes the top-most item from the stack (the newest item). The item is destructed.
     *
     * @return A boolean:
     *         - `true`:  An item was successfully popped.
     *         - `false`: The stack was empty.
     */
    bool pop()
    {
        bool success = false;

        if (!isEmpty()) {
            m_size--;
            reinterpret_cast<T*>(&m_storage[m_size])->~T();
            success = true;
        }

        return success;
    }

    /**
     * @brief Peek at the item on top of the stack.
     *
     * Retrieve a copy of the top-most item on the stack without removing it.
     *
     * @param[out] item
     *             The retrieved item.
     * @return A boolean:
     *         - `true`:  An item was successfully retrieved.
     *         - `false`: The stack was empty.
     */
    bool peek(T& item) const
    {
        bool success = false;

        if (!isEmpty()) {
            item = *reinterpret_cast<const T*>(&m_storage[m_size-1]);
            success = true;
        }

        return success;
    };

    /**
     * @brief Check if the stack is full.
     *
     * @return A boolean:
     *         - `true`:  The stack is full.
     *         - `false`: The stack is not full.
     */
    bool isFull() const
    {
        return (m_size >= Capacity);
    };

    /**
     * @brief Check if the stack is empty.
     *
     * @return A boolean:
     *         - `true`:  The stack is empty.
     *         - `false`: The stack is not empty.
     */
    bool isEmpty() const
    {
        return (m_size == 0);
    };

    /**
     * @brief Get the current number of items in the stack.
     *
     * @return The current number of items in the stack.
     */
    size_t size() const
    {
        return m_size;
    };

    /**
     * @brief Get the maximum number of items that can be stored by the stack.
     *
     * @return The maximum number of items that can be stored by the stack.
     */
    size_t capacity() const
    {
        return Capacity;
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

    /// The current number of items in the stack.
    size_t m_size = 0;

    /// The actual storage for the stack.
    StorageHelper m_storage[Capacity] {};
};

} // namespace junk

#endif // STACK_H
