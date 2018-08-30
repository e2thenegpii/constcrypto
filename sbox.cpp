#include "aes.hpp"

extern constexpr SBOX forward_sbox = initialize_aes_sbox();
extern constexpr SBOX reverse_sbox = initialize_inverse_aes_sbox();
extern constexpr ROUND_CONSTANTS rc = initialize_round_constants();
