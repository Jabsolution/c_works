#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long get_the_largest_prime_factor(long);

int main() {
    long no = 9007199254;
    long largest_prime_factor = 0;
    largest_prime_factor = get_the_largest_prime_factor(no);
    printf("The largest factor is: %ld", largest_prime_factor);
}

long get_the_largest_prime_factor(long no) {
    long range = sqrt(no);
    long factor = 0;
    long no_range = 0;

    for (no_range = 2; no_range <= range; no_range++) {
        while (!(no % no_range)) {
            no = no / no_range;
            if (no != 1)
                factor = no;
            printf("%ld ", no);
        }
    }
    return factor;
}

