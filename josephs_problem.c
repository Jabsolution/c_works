#include <stdio.h>
#include <stdlib.h>

int print_the_survivor(int);

int main() {
    int no = 14;
    printf("Survivor: %d\n", print_the_survivor(no));
}

int print_the_survivor(int no) {
    int survivor = 0;

    if (no == 1)
        return 1;

    if (!(no % 2)) {
        survivor = 2 * print_the_survivor(no/2) - 1;
    } else {
        survivor = 2 * print_the_survivor(no/2) + 1;
    }
    return survivor;
}


