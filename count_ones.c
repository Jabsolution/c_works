#include <stdio.h>
#include <stdlib.h>

int main() {
    int no = 15;
    int count = 0;

    while (no) {
        no &= (no - 1);
        count++;
    }
    printf("Number of ones:%d", count);
}

