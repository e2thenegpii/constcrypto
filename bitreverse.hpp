#pragma once
#include <cstddef>
#include <cstdint>

/**
 * Default algorithm to bit reverse read out one side and put in the other
 * @param in the value to reverse bits
 * @return the input parameter with the bit order reversed
 */
template <typename T>
constexpr T bitreverse(T in) {
    T out = 0;
    constexpr T numbits = sizeof(in) * 8;
    constexpr T highbit = 0x01 << (numbits - 1);

    //This for loop could be optimized to 
    for( size_t i = 0; i < numbits; ++i ) {
        out >>= 1;
        if( in & highbit) {
            out |= highbit;
        }
    }
    return out;
}

/**
 * Standard 8-bit bit-swap algorithm
 */
template<>
constexpr uint8_t bitreverse<uint8_t>(uint8_t in) {
    in = (in & 0xF0) >> 4 | (in & 0x0F) << 4;
    in = (in & 0xCC) >> 2 | (in & 0x33) << 2;
    in = (in & 0xAA) >> 1 | (in & 0x55) << 1;
    return in;
}

/**
 * Standard 16-bit bit-swap algorithm
 */
template<>
constexpr uint16_t bitreverse<uint16_t>(uint16_t in) {
    in = (in & 0xFF00) >>  8 | (in & 0x00FF) <<  8;
    in = (in & 0xF0F0) >>  4 | (in & 0x0F0F) <<  4;
    in = (in & 0xCCCC) >>  2 | (in & 0x3333) <<  2;
    in = (in & 0xAAAA) >>  1 | (in & 0x5555) <<  2;
    return in;
}

/**
 * Standard 32-bit bit-swap algorithm
 */
template<>
constexpr uint32_t bitreverse<uint32_t>(uint32_t in) {
    in = (in & 0xFFFF0000) >> 16 | (in & 0x0000FFFF) << 16;
    in = (in & 0xFF00FF00) >>  8 | (in & 0x00FF00FF) <<  8;
    in = (in & 0xF0F0F0F0) >>  4 | (in & 0x0F0F0F0F) <<  4;
    in = (in & 0xCCCCCCCC) >>  2 | (in & 0x33333333) <<  2;
    in = (in & 0xAAAAAAAA) >>  1 | (in & 0x55555555) <<  2;
    return in;
}

/**
 * Standard 64-bit bit-swap algorithm
 */
template<>
constexpr uint64_t bitreverse<uint64_t>(uint64_t in) {
    in = (in & 0xFFFFFFFF00000000ul) >> 32 | (in & 0x00000000FFFFFFFFul) << 32;
    in = (in & 0xFFFF0000FFFF0000ul) >> 16 | (in & 0x0000FFFF0000FFFFul) << 16;
    in = (in & 0xFF00FF00FF00FF00ul) >>  8 | (in & 0x00FF00FF00FF00FFul) <<  8;
    in = (in & 0xF0F0F0F0F0F0F0F0ul) >>  4 | (in & 0x0F0F0F0F0F0F0F0Ful) <<  4;
    in = (in & 0xCCCCCCCCCCCCCCCCul) >>  2 | (in & 0x3333333333333333ul) <<  2;
    in = (in & 0xAAAAAAAAAAAAAAAAul) >>  1 | (in & 0x5555555555555555ul) <<  2;
    return in;
}

