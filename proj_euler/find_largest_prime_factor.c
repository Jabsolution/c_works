/*
 * Project Eular: Problem - 3
 *
 * Find largest prime factor of a number.
 *
 * i.e.
 *
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143 ?
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long get_the_largest_prime_factor(long);

int main() {
    long no = 600851475143 ;
    long largest_prime_factor = 0;
    largest_prime_factor = get_the_largest_prime_factor(no);
    printf("The largest factor is: %ld", largest_prime_factor);
}

long get_the_largest_prime_factor(long no) {
    long range = sqrt(no);
    long factor = 1;
    long no_range = 0;

    if (range < 2) {
        return no;
    }
    for (no_range = 2; no_range <= range; no_range++) {
        while (!(no % no_range)) {
            no = no / no_range;
            if (no != 1) {
                factor = no;
                printf("%ld ", no_range);
            }
        }
    }
    printf("%ld ", factor);
    return factor;
}

