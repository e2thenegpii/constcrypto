#include "affine.hpp"
#include <array>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "gf2.hpp"

int main(int argc, char** argv) {
    const size_t loops = 1000000;
    uint8_t affine = 0x1F;
    uint8_t coefficient = 0xC6;
    auto a = affine_transform(0xCA, affine, coefficient);
    size_t x = 0;

    std::cout << std::setw(2) << std::setfill('0') << (int)a << std::endl;
    
    std::array<uint8_t, 256> input;
    std::generate(input.begin(), input.end(), [n=0]() mutable { return n++; });

    std::cout << std::chrono::high_resolution_clock::period::den << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < loops; ++i ) {
        for(auto val : input) {
            x += affine_transform(val, affine, coefficient);
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::cout << "Original: sum " << x << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()/(double)loops << " seconds per iteration" << std::endl;

    return 0;
}
