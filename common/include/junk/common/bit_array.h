/**
 * @file   bit_array.h
 * @brief  This file contains the definition of the BitArray container.
 * @author Liam Bucci <liam.bucci@gmail.com>
 * @date   2018-01-31
 * @copyright Copyright (c) 2018 Liam Bucci. See included LICENSE file.
 */

#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstdint>
#include <cstring>

#include "junk/common/junk_assert.h"

namespace junk {

/**
 * @brief Stores an array of bits and provides easy access to individual bits.
 *
 * BitArray stores an array of bits and provides a similar interface to those bits as an array would
 * normally provide (e.g. array index operator).
 *
 * @tparam Bits
 *         Number of bits stored in the BitArray.
 */
template <size_t Bits>
class BitArray {
public:
    /**
     * @brief Helper class used to reference an individual bit and modify its value.
     *
     * A BitReference is returned whenever a BitArray needs to provide an interface for modifying an
     * individual bit. For example, a BitReference is returned from the array index operator so that
     * the result of an index can be modified:
     * ```
     * my_array[0] = false;
     * ```
     */
    class BitReference {
    public:
        ~BitReference() = default;

        BitReference(const BitReference& b) = default;
        BitReference& operator=(const BitReference& b) = default;

        /**
         * @brief Assignment operator for a BitReference.
         *
         * Allows an individual bit in a BitArray to be modified.
         *
         * @param[in] val
         *            The value to change the bit to.
         */
        BitReference& operator=(bool val)
        {
            if (val) {
                m_byte |= (1 << m_offset);
            } else {
                m_byte &= ~(1 << m_offset);
            }

            return *this;
        };

        /**
         * @brief Boolean cast operator.
         *
         * Allows a BitReference to be cast to a bool. The cast takes the value of the bit this
         * BitReference represents.
         *
         * @return The bit value that this BitReference represents.
         */
        operator bool() const
        {
            return (bool)(m_byte & (1 << m_offset));
        };

        /**
         * @brief Invert operator.
         *
         * @return The inverse of the bit value represented by this BitReference.
         */
        bool operator~() const
        {
            return !(bool)(*this);
        };

        /**
         * @brief Toggle the bit represented by this BitReference.
         * @
         * @return A reference to this BitReference for chaining.
         */
        BitReference& toggle()
        {
            m_byte = (m_byte ^ (1 << m_offset));
            return *this;
        };

    private:
        /**
         * @brief BitReference constructor.
         *
         * By defining this as private, a BitReference may only be created by BitArray.
         *
         * @param[in] byte
         *            A reference to the byte that contains the bit that this BitReference
         *            represents.
         * @param[in] offset
         *            The bit number in the byte that this BitReference represents. Where
         *            zero is the LSB and 7 is the MSB.
         */
        explicit BitReference(uint8_t& byte, uint8_t offset)
            : m_byte(byte), m_offset(offset) {}

        /// A reference to the byte containing the bit that this BitReference represents.
        uint8_t& m_byte;
        /// The bit number in the byte that this BitReference represents. Where zero is the LSB and
        /// 7 is the MSB.
        uint8_t m_offset;

        // Allow BitArray to construct a BitReference
        friend class BitArray;
    };

    /// Default constructor.
    BitArray() = default;
    /**
     * @brief Constructor which initializes all bits in the array.
     *
     * @param[in] init
     *            The initial value to give all bits in the array.
     */
    BitArray(bool init)
    {
        if( init ) {
            memset(&m_bits[0], 0xFF, kNumBytes);
        } else {
            memset(&m_bits[0], 0x00, kNumBytes);
        }
    };
    /// Default destructor.
    ~BitArray() = default;

    /**
     * @brief Array index operator.
     *
     * Allows access to each bit by indexing into the bit array. Bits may not be modified by this
     * interface.
     *
     * @note Indexes are not checked before accessing. Indexes past the end of the array will cause
     *       undefined behavior.
     *
     * @param[in] index
     *            The index of the bit to access.
     * @return The value of the bit at position *index*.
     */
    bool operator[](size_t index) const
    {
        const size_t byte = (index / kBitsPerByte);
        const size_t offset = (index % kBitsPerByte);
        return (bool)(m_bits[byte] & (1 << offset));
    };

    /**
     * @brief Array index operator.
     *
     * Allows access to each bit by indexing into the bit array. Bits may be modified through the
     * returned BitReference.
     *
     * @note Indexes are not checked before accessing. Indexes past the end of the array will cause
     *       undefined behavior.
     *
     * @param[in] index
     *            The index of the bit to access.
     * @return A BitReference which allows modifications to the indexed bit.
     */
    BitReference operator[](size_t index)
    {
        const size_t byte = (index / kBitsPerByte);
        const size_t offset = (index % kBitsPerByte);
        return BitReference(m_bits[byte], offset);
    };

    /**
     * @brief Gets the value of the bit at an index.
     *
     * Allows access to each bit by indexing into the bit array. Bits may not be modified by this
     * interface.
     *
     * @note The provided index is asserted for validity, unlike the operator[] interface.
     *
     * @param[in] index
     *            The index of the bit to access.
     * @return The value of the bit at position *index*.
     */
    bool at(size_t index)
    {
        JUNK_ASSERT(index < Bits);
        return (*this)[index];
    };

    /**
     * @brief Gets the number of bits stored in this array.
     *
     * @return The number of bits stored in this array.
     */
    size_t size() const
    {
        return Bits;
    };

private:
    /// Number of bits per byte.
    static constexpr size_t kBitsPerByte = 8;
    /// Total number of bytes necessary to store all bits.
    static constexpr size_t kNumBytes = (Bits + kBitsPerByte - 1) / kBitsPerByte;
    /// The actual storage of all bits.
    uint8_t m_bits[kNumBytes] = {0};
};

} // namespace junk

#endif // BITARRAY_H
