#pragma once
#include <cstdint>
#include "bitreverse.hpp"
#include "rotate.hpp"

/**
 * An enum inform the affine transform of the endianness of the coefficient and affine multiplier
 */
enum class BITWISE_ENDIANESS : uint8_t {
    BIG,    ///< Most significant bit first (the normal what you'd expect for bytes)
    LITTLE  ///< Least significant bit first (speeds up the affine transform a bit)
};

/**
 * Computes an Affine transform over GF2**8
 * 
 * @todo extend this to use the gf2 class
 * @param x The value to transform
 * @param m The multiplier for the transform
 * @param b The constant to add to the product of in and affine
 * @return The result of the affine transform y = m*x + b over GF2
 */
template<BITWISE_ENDIANESS endian = BITWISE_ENDIANESS::BIG>
constexpr uint8_t affine_transform(uint8_t x, uint8_t m, uint8_t b) {
    
    uint8_t y = 0;

    if constexpr (endian == BITWISE_ENDIANESS::BIG) {    
        m = bitreverse<uint8_t>(m);
        b = bitreverse<uint8_t>(b);
    }

    for( int8_t i = 7; i >= 0; --i ) {
        y |= (__builtin_popcount(m & x) & 0x01) << i;
        m = ROTL<uint8_t, 7>(m);
    }

    return y ^ b;
}
