#include <stdio.h>
#include <stdlib.h>

int main() {
    short i = 0x1214;
    unsigned char *byte = (unsigned char *)&i;

    printf("%d", *byte);
    printf("ptr size %lu", sizeof(int *));

    if (*byte == 14) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }
}

