#include <stdio.h>
#include <stdlib.h>

int getbits(int, int, int);

int main() {
    int a = 10;
    int p = 2;
    int n = 3;

    printf("%d", getbits(a, p, n));
}

int getbits(int a, int p, int n) {
    a = (a >> (p+1-n)) & ~(~0 << n);
    return a;
}


