#include "sbox-c.h"
#include <stdio.h>

int main(int argc, char** argv) {
    for(size_t i = 0; i < 256; ++i ) {
        printf("%02x ", forward_sbox[i]);
        if ( i % 16 == 15) {
            printf("\n");
        }
    }
    return 0;
}
