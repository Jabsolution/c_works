#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 1011;
    int quo = a;
    int rem = 0;
    int val = 0;
    int seed = 1;
    int base = 10;

    while (quo) {
        rem = quo % base;
        quo = quo / base;

        val = (seed * rem) + val;
        seed = seed * 2;
    }
    printf("%d ", val);
}
