#include <stdio.h>
#include <stdlib.h>

int main() {
    uint64_t m1  = 0x5555555555555555;
    uint64_t m2  = 0x3333333333333333;
    uint64_t m4  = 0x0F0F0F0F0F0F0F0F;
    uint64_t m8  = 0x00FF00FF00FF00FF;
    uint64_t m16 = 0x0000FFFF0000FFFF;
    uint64_t m32 = 0x00000000FFFFFFFF;

    uint64_t x = 15;

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = (x & m8) + ((x >> 8) & m8);
    x = (x & m16) + ((x >> 16) & m16);
    x = (x & m32) + ((x >> 32) & m32);
    
    printf("Number of ones:%llu", x);
}

