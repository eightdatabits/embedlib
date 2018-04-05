/**
 * @file      typed_mem_pool.h
 * @brief     This file contains the TypedMemPool definition.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2018-03-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef TYPED_MEM_POOL_H
#define TYPED_MEM_POOL_H

#include <stdint.h>
#include <queue>

#include "junk/memory/mem_pool.h"

namespace junk {


template <typename T, size_t S>
class TypedMemPool final : public MemPool<sizeof(T), S, alignof(T)>
{
    using BaseMemPool = MemPool<sizeof(T), S, alignof(T)>;
public:
    TypedMemPool() = default;
    /// @todo Destruct all allocated blocks
    ~TypedMemPool() = default;

    T* allocate()
    {
        return static_cast<T*>(BaseMemPool::allocate(sizeof(T)));
    }

    T* store(const T& item)
    {
        T* ptr = allocate();

        if (ptr != nullptr) {
            new (ptr) T(item);
        }

        return ptr;
    }

    T* store(T&& item)
    {
        T* ptr = allocate();

        if (ptr != nullptr) {
            new (ptr) T(std::move(item));
        }

        return ptr;
    }

    template <typename ... Args>
    T* emplace(Args&&... args)
    {
        T* ptr = allocate();

        if (ptr != nullptr) {
            new (ptr) T(std::forward<Args>(args)...);
        }

        return ptr;
    }

    void deallocate(T* ptr)
    {
        if (BaseMemPool::isValid(static_cast<void*>(ptr))) {
            ptr->~T();
            BaseMemPool::deallocate(static_cast<void*>(ptr));
        }
    }
};

} // namespace junk

#endif // TYPED_MEM_POOL_H
