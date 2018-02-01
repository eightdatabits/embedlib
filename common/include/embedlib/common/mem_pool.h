/**
 * @file      mem_pool.h
 * @brief     This file contains the MemPool definition.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-12-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdint.h>
#include <queue>

#include "embedlib/common/iallocator.h"

namespace emb {

/**
 * @brief A memory pool that statically allocates its memory internally.
 *
 * This memory pool statically allocates enough memory to hold `NumBuckets` worth of
 * `BucketSize` buckets. The buckets are by default aligned to their size, but the alignment may be
 * set via the `BucketAlign` template parameter. Allocations allocate a single bucket at a time and
 * the memory pool keeps track of the buckets available for allocation.
 *
 * @warning There is no protection for overrunning a bucket, so an owner of one bucket could
 *          accidentally access or modify data in another bucket.
 * @warning The class does not provide a thread-safe API.
 *
 * @tparam BucketSize
 *         The size in bytes of a bucket. Does not take into account padding bytes due to alignment.
 * @tparam NumBuckets
 *         The total number of buckets this MemPool must be able to allocate.
 * @tparam BucketAlign
 *         The alignment of each bucket. Defaults to alignment of size_t.
 */
template <size_t BucketSize, size_t NumBuckets, size_t BucketAlign = BucketSize>
class MemPool final : public IAllocator
{
public:
    /**
     * @brief MemPool constructor.
     *
     * Initializes all MemPool internals.
     */
    MemPool()
    {
        for (size_t i = 0; i < NumBuckets; i++) {
            m_alloc_queue.push(&m_buckets[i]);
        }
    };
    /// MemPool destructor.
    ~MemPool() = default;

    /**
     * @brief Allocate a block at least as large as size.
     *
     * Allocates a bucket from the pool. If *size* is larger than a bucket `nullptr` is returned.
     * If no buckets are available `nullptr` is returned.
     *
     * @param[in] size
     *            The size in bytes of the requested block of memory. Must be less than or equal to
     *            BucketSize.
     * @return A pointer to the allocated bucket. `nullptr` on failure to allocate.
     */
    void* allocate(size_t size)
    {
        void* addr = nullptr;

        if ((size <= BucketSize) && (m_alloc_queue.size() > 0)) {
            addr = m_alloc_queue.front();
            m_alloc_queue.pop();
        }

        return addr;
    };

    /**
     * @brief Returns the given bucket back to the pool.
     *
     * Returns a previously allocated bucket back to the pool. *mem* must point to a valid,
     * previously allocated bucket. If the pointer is not a valid bucket it will be ignored.
     * `nullptr` is ignored. *mem* must not have already been deallocated.
     *
     * @param[in]  mem
     *             A pointer to the bucket to deallocate. Must not have already been deallocated.
     *             May be `nullptr`.
     */
    void deallocate(void* mem)
    {
        if (mem == nullptr) {
            return;
        }

        // Check that this is a "valid" bucket
        if ((mem >= &m_buckets[0]) && (mem <= &m_buckets[NumBuckets]) && ((((uintptr_t)mem - (uintptr_t)&m_buckets[0]) % BucketSize) == 0)) {
            m_alloc_queue.push(mem);
        }
    };

    /**
     * @brief Get the current number of available buckets.
     *
     * @return The current remaining number of available buckets.
     */
    size_t available() const
    {
        return m_alloc_queue.size();
    };

    /**
     * @brief Get the current number of buckets that have been allocated.
     *
     * @return The current number of unavailable (allocated) buckets.
     */
    size_t reserved() const
    {
        return NumBuckets - m_alloc_queue.size();
    };

private:
    /// The internal helper object for creating buckets of the right size and alignment.
    struct alignas(BucketAlign) Bucket
    {
        uint8_t mem[BucketSize] {};
    };

    /// A queue of Bucket pointers which are available for allocation.
    std::queue<void*> m_alloc_queue {};
    /// The actual storage of all buckets.
    Bucket m_buckets[NumBuckets] {};
};

} // namespace emb

#endif // MEM_POOL_H
