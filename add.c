#include <stdio.h>
#include <stdlib.h>

void print_addition(int, int);

int main() {
    int a = 3;
    int b = 6;

    print_addition(a, b);
}

void print_addition(int a, int b) {
    int c = 0;
    if (!a || !b) {
        c = a ^ b;
        printf("%d", c);
        return;
    }

    c = a;
    while (c) {
        c = (a & b);
        c <<= 1;
        a = (a ^ b);
        b = c;
    }
    printf("%d", a);
}

