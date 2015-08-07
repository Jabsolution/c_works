#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ascii[2] = {0xFE, 0x10};
    unsigned short data_len = 0xFE10;

    if (data_len == 0xFE10) {
        printf("ASCII before %x\n", data_len);
    }
    memcpy(&data_len, ascii, 2);
    data_len = ntohs(data_len);

    if (data_len == 0xFE10) {
        printf("ASCII %#x\n", data_len);
    }

}

