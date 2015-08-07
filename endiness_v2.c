#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union _c {
    unsigned int i;
    char no;
} c;

int main() {
    c number;
    memset(&number, 0, sizeof(c));
    number.i = 0xFBFC;

    if (number.no == (char)0xFC) {
        printf("%d", number.no);
        printf("The system is little endian\n");
    } else {
        printf("The system is big endian\n");
    }
}
