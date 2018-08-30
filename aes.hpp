#include <array>
#include "gf2.hpp"
#include "affine.hpp"

using SBOX = std::array<uint8_t, 256>;
using ROUND_CONSTANTS = std::array<uint32_t, 30>;

/**
 * Generates the Key Expansion round constants for the given polynomial
 * 
 * @param polynomial The GF2_8 polynomial for generation
 * @param base The base of the exponent
 * @return A round constants array
 */
template< uint8_t polynomial = 0x1B, uint8_t base = 2>
constexpr ROUND_CONSTANTS initialize_round_constants() {
    gf2_8<polynomial> temp = 1;
    ROUND_CONSTANTS rc = {0};

    for( auto &elem : rc ) {
        elem = temp;
        temp *= base;
    }

    return rc;
}

/**
 * Generates an AES SBOX
 *
 * @param polynomial the GF2 polynomial to be used
 * @param generator_index Selects the specific generator for the given polynomial, however this parameter is actually redundant as one of the properties of the S-BOX is that it is invertible as such the generator only effects the order in which the values are initialized not their actual values.
 * @param affine The multiplier of the affine transformation
 * @param coefficient The value to add in the affine transformation
 * @param affin_endianess Tells the algorithm if the affine and coefficient parameters are in big or little endian bit format (little endian format saves a half dozen instructions on x86, but if you're using this for as a constexpr as you should then it shouldn't matter
 * @return A Rijndael S-Box
 */
//this code is optimized for the AES_sbox
//It needs to be fixed to properly calculate the gmul_inverse and the affine transform
template <  uint8_t polynomial = 0x1B,
            uint8_t generator_index = 0,
            uint8_t affine = 0x1F,
            uint8_t coefficient = 0xC6,
            BITWISE_ENDIANESS affine_endianess = BITWISE_ENDIANESS::BIG>
constexpr SBOX initialize_aes_sbox() {

    static_assert(is_cyclic_over_gf256<polynomial>::value, "polynomial must be prime over GF2**8");
    static_assert(sizeof(is_cyclic_over_gf256<polynomial>::generators) > generator_index, "generator_index is to big");

    constexpr gf2_8<polynomial> generator = is_cyclic_over_gf256<polynomial>::generators[generator_index];
    constexpr gf2_8<polynomial> gen_inv = gf2_8<polynomial>::invert(generator);

    gf2_8<polynomial> p = 1, q = 1;
    SBOX sbox = {0};

    // 0 is a special case since it has no inverse
    sbox[0] = affine_transform<affine_endianess>(0, affine, coefficient);

    for( uint16_t i = 0; i < sbox.size() - 1; ++i ) { //255 because sbox[0] is already done
        p *= generator;
        q *= gen_inv;

        sbox[p] = affine_transform<affine_endianess>(q, affine, coefficient);
    }

    return sbox;
}

/**
 * Generates the inverse Rijndael S-Box
 * @note The parameters are for generating the forward S-Box which we then invert
 * @see initialize_aes_sbox
 */
template <  uint8_t polynomial = 0x1B,
            uint8_t generator_index = 0,
            uint8_t affine = 0x1F,
            uint8_t coefficient = 0xC6,
            BITWISE_ENDIANESS affine_endianess = BITWISE_ENDIANESS::BIG>
constexpr SBOX initialize_inverse_aes_sbox() {
    SBOX sbox = initialize_aes_sbox<polynomial, generator_index, affine, coefficient, affine_endianess>();
    SBOX inverse = {0};

    for( size_t i = 0; i < sbox.size(); ++i ) {
        inverse[sbox[i]] = i;
    }
    return inverse;
}
