#include <stdio.h>
#include <stdlib.h>

int comp_op(int, int, int);

int main() {
    int a = 0;
    int b = 3;
    int c = 2;

    printf("%d", comp_op(a, b, c));

}

int comp_op(int a, int b, int c) {
    return (((~a) & c));
}

