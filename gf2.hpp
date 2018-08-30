#pragma once
#include <cstdint>
#include <array>
#include "cyclic.hpp"

/**
 * Preforms mathematical operations in GF2
 */
template <typename T, T polynomial, size_t num_bits = sizeof(T) * 8> class gf2 {
private:
    //This doesn't scale well to uint32_t
    static constexpr size_t MAX_VAL = 1 << (sizeof(T) * 8);
    using LOG_TABLE = std::array<T, MAX_VAL>;
public:
    constexpr gf2(T v) : value(v) {};
    gf2(const gf2& other) = default;
    gf2(gf2&& other) = default;
    ~gf2() = default;

    constexpr gf2& operator =(const gf2& other) { this->value = other.value; return *this; }
    constexpr gf2& operator +=(const gf2& rhs) { *this = *this + rhs; return *this; }
    constexpr gf2 operator +(const gf2& rhs) { return this->value ^ rhs.value; } // Addition over GF2 is just bitwise xor
    constexpr gf2 operator +(const T& rhs) { return *this + gf2(rhs); }

    constexpr gf2& operator -=(const gf2& rhs) { *this += rhs; return *this; }
    constexpr gf2 operator -(const gf2& rhs) { return *this + rhs; } // Subtraction over GF2 is the same as addition
    constexpr gf2 operator -(const T& rhs) { return *this - gf2(rhs); }

    constexpr gf2& operator *=(const gf2& rhs) { *this = (*this * rhs); return *this; }
    constexpr gf2 operator *(const gf2& rhs) {
        gf2<T, polynomial, num_bits> product = 0;
        T m = rhs.value;
        gf2<T, polynomial, num_bits> multiplicand = *this;
        constexpr T highBitMask = 1 << (num_bits-1);

        for( size_t i = 0; i < num_bits; ++i ) {
            if((m & 1) == 1) {
                product += multiplicand;
            }   
            multiplicand = gf2(multiplicand << 1) + gf2(multiplicand & highBitMask ? polynomial : 0);
            m >>= 1;
        }
        return product;
    }

    static constexpr gf2<T, polynomial> invert(const gf2<T, polynomial> & other) {
        if( 0 != other.value ) {
            return gf2<T, polynomial>(gf2<T, polynomial>::alog[((MAX_VAL-1) - gf2<T, polynomial>::log[other.value])]);
        }
        return gf2<T, polynomial>(0);
    }

    constexpr operator T() const { return value; }

    bool operator==(const gf2& rhs) { return this->value == rhs.value; }
    bool operator!=(const gf2& rhs) { return this->value != rhs.value; }
    bool operator> (const gf2& rhs) { return this->value > rhs.value; }
    bool operator< (const gf2& rhs) { return this->value < rhs.value; }
    bool operator<=(const gf2& rhs) { return this->value <= rhs.value; }
    bool operator>=(const gf2& rhs) { return this->value >= rhs.value; }
private:
    static constexpr auto generate_atable(gf2<T, polynomial> generator) -> LOG_TABLE;
    static constexpr auto generate_ltable(const LOG_TABLE & atable) -> LOG_TABLE;
    T value;  ///< The actual value for the GF2
    
    static constexpr LOG_TABLE alog = gf2<T, polynomial>::generate_atable(is_cyclic_over_gf256<polynomial>::generators[0]);
    static constexpr LOG_TABLE log = gf2<T, polynomial>::generate_ltable(alog);
};

/**
 * Generates the Anti-Log table over GF2**8
 * @tparam polynomial - The irreducible modulus over GF2
 * @param generator - The generator to use for the log table
 * @return The generated log table
 */
template <typename T, T polynomial, size_t num_bits>
constexpr auto gf2<T, polynomial, num_bits>::generate_atable(gf2<T, polynomial> generator) -> LOG_TABLE {
    LOG_TABLE atable = {0};
    gf2<T, polynomial> a = 1;

    for( auto &elem : atable ) {
        elem = static_cast<T>(a);
        a *= generator;
    }

    return atable;
}

/**
 * Generates the log table over GF2
 * @tparam polynomial - The irreducible modulus over GF2
 * @param atable - The anti-log table to use for the log table generation
 */
template <typename T, T polynomial, size_t num_bits>
constexpr auto gf2<T, polynomial, num_bits>::generate_ltable(const LOG_TABLE & atable) -> LOG_TABLE {
    LOG_TABLE ltable = {0};
    for( uint16_t x = 0; x < ltable.size(); ++x ) {
        ltable[atable[x]] = x;
    }
    ltable[0] = 0;
    return ltable;
}

template <uint8_t polynomial> using gf2_8 = gf2<uint8_t, polynomial>;
template <uint16_t polynomial> using gf2_16 = gf2<uint16_t, polynomial>;
template <uint32_t polynomial> using gf2_32 = gf2<uint32_t, polynomial>;
