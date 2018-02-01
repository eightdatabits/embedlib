/**
 * @file      mem_pool_allocator.h
 * @brief     This file contains the MemPoolAllocator definition.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-12-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef MEM_POOL_ALLOCATOR_H
#define MEM_POOL_ALLOCATOR_H

#include <cstdint>
#include <climits>

#include "embedlib/common/emb_assert.h"
#include "embedlib/common/mem_pool.h"

namespace emb {

template <size_t Bits>
class BitArray {
public:
    BitArray() = default;
    BitArray(bool init)
    {
        if( init ) {
            memset(&bits[0], 0xFF, kNumBytes);
        } else {
            memset(&bits[0], 0x00, kNumBytes);
        }
    };
    ~BitArray() = default;

    bool operator[](size_t index)
    {
        bool val = false;
        return val;
    };

    bool at(size_t index)
    {
        EMB_ASSERT(index < Bits);
        return (*this)[index];
    };

private:
    constexpr size_t kNumBytes = (Bits + 7) / 8;
    uint8_t m_bits[kNumBytes] = {0};
};

template <size_t BucketSize, size_t NumBuckets, size_t Alignment = alignof(BucketSize)>
class MemPool final : public IAllocator
{
public:
    MemPool()
    {
        for (void* bucket : m_buckets) {
            m_alloc_queue.push(bucket);
        }
    };
    ~MemPool() = default;

    void* allocate(size_t size)
    {
        void* addr = nullptr;

        if ((size <= BucketSize) && (m_alloc_queue.size() > 0)) {
            addr = m_alloc_queue.front();
            m_alloc_queue.pop();
        }

        return addr;
    };

    void deallocate(void* mem)
    {
        if (mem == nullptr) {
            return;
        }

        // Check that this is a "valid" bucket
        if ((mem >= &m_buckets[0]) && (mem <= &m_buckets[NumBuckets]) && (((mem - &m_buckets[0]) % BucketSize) == 0)) {
            m_alloc_queue.push(mem);
        }
    };

    size_t available() const
    {
        return m_alloc_queue.size();
    };

    size_t reserved() const
    {
        return NumBuckets - m_alloc_queue.size();
    };

private:
    struct Bucket
    {
        uint8_t mem[BucketSize] {};
    };

    std::queue<void*> m_alloc_queue {};
    alignas(Alignment) Bucket m_buckets[NumBuckets] {};
};

/**
 * @brief A memory pool that statically allocates its memory internally.
 *
 * This memory pool statically allocates enough memory to hold `NumBuckets` worth of
 * `BucketSizeBytes` buckets with alignment `BucketAlign`. Allocations allocate a single bucket at
 * a time and the memory pool keeps track of which buckets have been allocated and which are free.
 *
 * Buckets are aligned to `BucketAlign` boundaries. This means that there may be padding between
 * buckets. For example, if `BucketSizeBytes` is 3 and `BucketAlign` is alignof(uint32_t) then each
 * bucket will be on a 0x04 byte boundary with a one byte padding between buckets.
 *
 * @warning There is no protection for overrunning a bucket, so an owner of one bucket could
 *          accidentally access or modify data in another bucket.
 *
 * @tparam BucketSizeBytes
 *         The size in bytes of a bucket. Does not take into account padding bytes due to alignment.
 * @tparam NumBuckets
 *         The total number of buckets this MemPool must be able to allocate.
 * @tparam BucketAlign
 *         The alignment of each bucket. Defaults to alignment of size_t.
 */
template <size_t BucketSizeBytes, size_t NumBuckets, size_t BucketAlign = alignof(size_t)>
class StaticMemPool final : IMemPool {
public:
    /// Default constructor
    StaticMemPool() = default;
    /// Default destructor
    ~StaticMemPool() = default;




    /**
     * @brief Keeps track of allocation status of all buckets.
     *
     * A bucket bin is a bit field that keeps track of the allocation status of buckets. Each bit
     * represents a single bucket: 0 represents a free bucket, 1 represents an allocated bucket.
     *
     * The number of bins necessary to keep track of `NumBuckets` buckets is a factor of the number
     * of bits in each bin as well as the number of buckets. These calculations are done statically
     * at compile-time and set the number of bins used to track all buckets. For example, if a bin
     * is a 32-bit value and there are 31 buckets a single bin may be used. However, if there are
     * 33 buckets then two bins must be used.
     */
    BucketBin m_bucket_bins[kNumBucketBins] = {};
};

class MemPoolAllocator {
public:
    /// Default constructor
    MemPoolAllocator() = default;
    /// Default destructor
    ~MemPoolAllocator() = default;

    void* allocate(size_t size) {

    }

    /**
     * @brief Releases a bucket back to the pool.
     *
     * @param[in]  mem
     *             A pointer to the first byte of the bucket to be released. This must be the same
     *             pointer as was returned from alloc().
     */
    void deallocate(void* mem) {

    }

    /**
     * @brief Get the size of a bucket in bytes.
     *
     * @return The size of a bucket in bytes.
     */
    size_t bucketSize() const {
        return BucketSizeBytes;
    }

    /**
     * @brief Get the maximum number of buckets that can be allocated.
     *
     * @return The maximum number of buckets that can be allocated.
     */
    size_t numBuckets() const {
        return NumBuckets;
    }

    /**
     * @brief Get the current number of free buckets in this MemPool.
     *
     * @return The current number of free buckets in this MemPool.
     */
    size_t remaining() const {
        return m_remaining;
    }

    /**
     * @brief Get the current number of allocated buckets in this MemPool.
     *
     * @return The current number of allocated buckets in this MemPool.
     */
    size_t allocated() const {
        return (NumBuckets - m_remaining);
    }

private:

};

} // namespace emb

#endif // STATIC_MEM_POOL_H
