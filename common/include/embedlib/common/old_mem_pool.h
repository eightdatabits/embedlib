/**
 * @file      mem_pool.h
 * @brief     This file contains the MemPool definition.
 * @author    Liam Bucci <liam.bucci@gmail.com>
 * @date      2017-12-21
 * @copyright Copyright (c) 2017 Liam Bucci. See included LICENSE file.
 */

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <cstdint>
#include <climits>

#include "emblib/common/emb_assert.h"

namespace emb {

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
template <size_t BucketSizeBytes, size_t NumBuckets, size_t Alignment = alignof(BucketSizeBytes)>
class PoolStorage {
public:
    PoolStorage() = default;
    ~PoolStorage() = default;

private:
    friend class MemPool;

    struct alignas(BucketAlign) Bucket {
        uint8_t mem[BucketSizeBytes] = {};
    };

    Bucket buckets[NumBuckets] = {};
    bool
};

class MemPool {
public:
    template <size_t BucketSizeBytes, size_t NumBuckets, size_t BucketAlign>
    MemPool(Storage<BucketSizeBytes, NumBuckets, BucketAlign>& storage)
        : kBucketSize(BucketSizeBytes),
          kNumBuckets(NumBuckets),
          m_buckets(storage.buckets) {}
    ~MemPool() = default;

    void* operator[](size_t index)
    {
        size_t offset = index * kBucketSize;
        return &reinterpret_cast<uint8_t*>(m_mem)[offset];
    }

    void* at(size_t index)
    {
        EMB_ASSERT(index <= kNumBuckets);
        return *this[index];
    }

    /**
     * @brief Get the maximum number of buckets that can be allocated.
     *
     * @return The maximum number of buckets that can be allocated.
     */
    size_t buckets() const
    {
        return kNumBuckets;
    }

    /**
     * @brief Get the size of a bucket in bytes.
     *
     * @return The size of a bucket in bytes.
     */
    size_t bucketSize() const
    {
        return kBucketSize;
    }

private:
    friend class MemPoolAllocator;

    const size_t kBucketSize;
    const size_t kNumBuckets;

    static constexpr size_t headerSize(size_t num_buckets) {
        return (num_buckets + CHAR_BIT - 1) / CHAR_BIT;
    }

    /**
     * @brief Reserve a bucket.
     *
     * @return A pointer to the first byte of a bucket.
     */
    void* reserve() {
        void* bucket = nullptr;

        if (m_remaining != 0) {
            for (size_t i = 0; i < NumBuckets; i++) {
                const size_t bin = (i / kBucketsPerBin);
                const size_t offset = (i % kBucketsPerBin);

                if ((m_bucket_bins[bin] & (1 << offset)) == 0) {
                    // Bucket has not been allocated yet
                    m_bucket_bins[bin] |= (1 << offset);
                    bucket = static_cast<void*>(&m_buckets[i].mem[0]);
                    m_remaining--;
                    break;
                }
            }
        }

        return bucket;
    }

    /**
     * @brief Releases a bucket back to the pool.
     *
     * @param[in]  mem
     *             A pointer to the first byte of the bucket to be released. This must be the same
     *             pointer as was returned from allocate().
     */
    void release(void* mem) {
        const ptrdiff_t bucket_diff = static_cast<uint8_t*>(mem) - (&m_buckets[0].mem[0]);
        const size_t bucket_index = bucket_diff / sizeof(Bucket);

        // Check that the given memory is actually a bucket
        if ((bucket_diff % sizeof(Bucket)) == 0) {
            const size_t bin = (bucket_index / kBucketsPerBin);
            const size_t offset = (bucket_index % kBucketsPerBin);

            if (bin <= kNumBucketBins) {
                m_bucket_bins[bin] &= ~(1 << offset);
                m_remaining++;
            }
        }
    }

    /// A BucketBin keeps track of which buckets have been allocated and which are free.
    typedef size_t BucketBin;

    /// Number of buckets tracked per bin.
    static constexpr size_t kBucketsPerBin = sizeof(BucketBin) * CHAR_BIT;
    /// Number of bins total.
    static constexpr size_t kNumBucketBins = (NumBuckets + kBucketsPerBin - 1) / kBucketsPerBin;

    /// Keeps track of the number of remaining free buckets.
    size_t m_remaining = NumBuckets;

    /// The actual memory pool.
    void* m_mem = nullptr;
};

} // namespace emb

#endif // MEM_POOL_H
