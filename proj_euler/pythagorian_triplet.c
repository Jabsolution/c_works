#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 0;
    int b = 0;
    int n1 = 0;
    int a_b = 0;
    int c = 0;
    int n = 1000;
    int prod = 1;

    for (c = 1; c < n; c++) {
        a_b = n - c;
        n1 = a_b / 2;
        //printf("for c: %d\n", c);
        for (a = 1; a <= n1; a++) {
            b = a_b - a;
          //  printf("a: %d, b: %d\n", a, b);
            if ((a * a + b * b) == (c * c)) {
                printf("a: %d, b: %d, c: %d\n", a, b, c);
                prod = a * b * c;
                printf("Prod: %d\n", prod);

            }
        }
    }
}
