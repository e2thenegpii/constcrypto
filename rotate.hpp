#pragma once
#include <cstddef>
#include <cstdint>

template <typename T, size_t shift> constexpr T ROTL(T in) {
    constexpr T numbits = sizeof(in) * 8;
    return (in << shift) | (in >> (numbits - shift));
}

template <typename T> constexpr T ROTL(T in, T shift) {
    constexpr T numbits = sizeof(in) * 8;
    return (in << shift) | (in >> (numbits - shift));
}

