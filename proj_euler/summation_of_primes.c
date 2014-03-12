#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    unsigned long nth = 2000000;
    int ith = 0;
    int sq_root = 0;
    int i = 2;
    int j = 2;
    int is_prime = 0;
    unsigned long tot = 0;


    if (nth == 1)
        exit(0);

    while ((j < nth)) {
        sq_root = sqrt(j);

        if (sq_root <= 1) {
            ith++;
            //printf("%d: %d\n", ith, j);
            tot += j;
            j++;
            continue;
        }

        for (i = 2; i <= sq_root; i++) {
            if (!(j % i)) {
                is_prime = 0;
                break;
            }
            is_prime = 1;
        }
        if (is_prime) {
            ith++;
            //printf("%d: %d\n", ith, j);
            tot += j;
        }
        j++;
    }
    printf("Sum of primes: %ld\n", tot);
}
