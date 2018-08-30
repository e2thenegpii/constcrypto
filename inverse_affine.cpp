#include <iostream>
#include "affine.hpp"

int main(int argc, char** argv) {
    std::cout << (int)0 << " " << (int)affine_transform(0, 0x1F, 0xC6) << std::endl;
    std::cout << (int)0 << " " << (int)affine_transform(0, 0x4A, 0xA0) << std::endl;
//    for( uint8_t i = 0; i <= 255; i++ ) {
//        std::cout << (int)i << " " << (int)affine_transform(affine_transform(i, 0x1F, 0xC6), 0x4A, 0xA0) << std::endl;
//    }
    return 0;
}
