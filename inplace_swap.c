/*
 * Swap two numbers without using any extra memory
 *
 */
#include <stdio.h>
#include <stdlib.h>

void swap_inplace(int *, int *);
int main() {
    int x = 10;
    int y = 20;

    printf("The numbers are %d and %d\n", x, y);
    swap_inplace(&x, &y);
    printf("The number are %d and %d", x, y);
}

void swap_inplace(int *x, int *y) {
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}
