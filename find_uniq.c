#include <stdio.h>
#include <stdlib.h>

void print_uniq(int *, int);
int main() {
    int a[] = {1, 2, 1, 4, 6, 2};
    int size = sizeof(a) / sizeof(int);

    print_uniq(a, size);
}

void print_uniq(int *a, int size) {
    int x = 0;
    int y = 0;
    int right_most_bit = 0;
    int xor = 0;
    int i = 0;

    for (i = 0; i < size; i++) {
        xor ^= a[i];
    }

    right_most_bit = xor & ~(xor - 1);

    for (i = 0; i < size; i++) {
        if (a[i] & right_most_bit) {
            x ^= a[i];
        } else {
            y ^= a[i];
        }
    }

    printf("%d %d", x, y);

    }

