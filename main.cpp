#include <iostream>
#include <iomanip>
#include "sbox.h"

template <typename T, size_t width>
void print_array(const T& array) {
    std::cout << std::hex;
    for( size_t i = 0; i < sizeof(array)/sizeof(decltype(array.back())); ++i ) {
        std::cout << std::setw(2) << std::setfill('0') << (int)array[i];

        if( (width-1) == (i % width) ) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
}

int main(int argc, char** argv) {
    print_array<SBOX, 16>(forward_sbox);
    std::cout << std::endl;

    print_array<SBOX, 16>(reverse_sbox);
    std::cout << std::endl;

    print_array<ROUND_CONSTANTS, 16>(rc); 
    std::cout << std::endl;
    return 0;
}
