#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 10;
    int y = 20;

    &x = &y;

    printf("%d \n", x);
}
