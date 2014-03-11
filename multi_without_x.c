#include <stdio.h>
#include <stdlib.h>

void print_product(int, int);

int main() {
    int a = 3;
    int b = 4;

    print_product(a, b);
}

void print_product(int a, int b) {
    int c = 0;
    while(b) {
        if (b & 1) 
            c = c + a;
        a = a << 1;
        b = b >> 1;
    }
    printf("%d ", c);
}

