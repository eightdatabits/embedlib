/**
 * @file      iallocator.h
 * @brief     This file contains the common allocator interface.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-12-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include <cstdint>

namespace junk {

/**
 * @brief Interface definition for all allocator derived classes.
 */
class IAllocator {
public:
    virtual ~IAllocator() = default;

    /**
     * @brief Allocates a block of memory at least as large as the given size.
     *
     * ## API Requirements
     *
     * * On success a pointer to a free block of memory is returned. This block is at least as large
     *   as *size*.
     * * Returns `nullptr` if no free block is found which satisfies the size requirement.
     *
     * @return A pointer to the first byte of the allocated memory.
     */
    virtual void* allocate(size_t size) = 0;

    /**
     * @brief Returns a block of memory to the internal pool.
     *
     * ## API Requirements
     *
     * * Passing a pointer to a valid, allocated block of memory, causes that block will be returned
     *   to the allocator and be available for allocation.
     * * Passing `nullptr` is ignored.
     * * Passing a pointer that does not point to a valid block of memory for this allocator will
     *   be ignored.
     * * Passing a pointer that has already been deallocated causes undefined behavior.
     *
     * @param[in]  mem
     *             A pointer to the first byte of the block of memory being returned. Must be the
     *             same pointer as was originally returned from allocate().
     */
    virtual void deallocate(void* mem) = 0;

    /**
     * @brief Returns the current number of remaining free buckets.
     *
     * @return The current number of remaining free buckets.
     */
    virtual size_t available() const = 0;

    /**
     * @brief Returns the current number of allocated buckets.
     *
     * @return The current number of allocated buckets.
     */
    virtual size_t reserved() const = 0;
};

} // namespace junk

#endif // IALLOCATOR_H
