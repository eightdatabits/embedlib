
#ifndef MEM_POOL_ALLOCATOR_H
#define MEM_POOL_ALLOCATOR_H

#include <cstdint>
#include <climits>

class IMemPool {
public:
    virtual ~IMemPool() = 0;

    virtual void* alloc() = 0;
    virtual void dealloc(void* mem) = 0;

    virtual size_t bucketSize() const = 0;
    virtual size_t numBuckets() const = 0;
    virtual size_t remaining() const = 0;
    virtual size_t allocated() const = 0;
};

inline IMemPool::~IMemPool() {}

template <size_t BucketSizeBytes, size_t NumBuckets, typename BucketAlign = size_t>
class MemPool final : IMemPool {
public:
    MemPool() = default;
    ~MemPool() = default;

    void* alloc() {
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

    void dealloc(void* mem) {
        const ptrdiff_t bucket_diff = static_cast<uint8_t*>(mem) - (&m_buckets[0].mem[0]);
        const size_t bucket_index = bucket_diff / kBucketSpacing;

        // Check that the given memory is actually a bucket
        if ((bucket_diff % kBucketSpacing) == 0) {
            const size_t bin = (bucket_index / kBucketsPerBin);
            const size_t offset = (bucket_index % kBucketsPerBin);

            if (bin <= kNumBucketBins) {
                m_bucket_bins[bin] &= ~(1 << offset);
                m_remaining++;
            }
        }
    }

    size_t bucketSize() const {
        return BucketSizeBytes;
    }

    size_t numBuckets() const {
        return NumBuckets;
    }

    size_t remaining() const {
        return m_remaining;
    }

    size_t allocated() const {
        return (NumBuckets - m_remaining);
    }

private:
    struct alignas(BucketAlign) Bucket {
        uint8_t mem[BucketSizeBytes];
    };

    typedef uint32_t BucketBin;

    static constexpr size_t kBucketsPerBin = sizeof(BucketBin) * CHAR_BIT;
    static constexpr size_t kNumBucketBins = (NumBuckets + kBucketsPerBin - 1) / kBucketsPerBin;


    size_t m_remaining = NumBuckets;
    uint32_t m_bucket_bins[kNumBucketBins] = {};
    Bucket m_buckets[NumBuckets] = {};

    const size_t kBucketSpacing = (&m_buckets[1].mem[0]) - (&m_buckets[0].mem[0]);
};

/*
template <typename BucketT, size_t NumBuckets>
class TypedMemPool final : IMemPool {
public:
    TypedMemPool();
    ~TypedMemPool();

    template <typename BucketT>
    void* alloc();
    void dealloc(void* mem);

    size_t bucketSize() const {
        return sizeof(BucketT);
    }

    size_t numBuckets() const {
        return NumBuckets;
    }

    size_t remaining() const;
    size_t allocated() const;
};

class MemPoolAllocator {
public:
    MemPoolAllocator(void* memory, size_t size_bytes);
    ~MemPoolAllocator();


};
*/
#endif // MEM_POOL_ALLOCATOR_H
