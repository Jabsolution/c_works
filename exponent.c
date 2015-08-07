#include <stdio.h>
#include <stdlib.h>

int main() {
    int total = 1;
    int base = 9;
    int exponent = 2;
    int i = 0;

    for (i = 1; i <= exponent; i++) {
        total *= base;
    }
    printf("%d ", total);

}

