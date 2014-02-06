#include <stdio.h>
#include <stdlib.h>

void bin_add(int, int, int, int, int);

int main() {
    int a = 101;
    int b = 101;
    bin_add(a, b, 0, 1, 0);
}

void bin_add(int a, int b, int carry, int base_ten, int bin_sum) {
    int qa = 0;
    int qb = 0;
    int ra = 0;
    int rb = 0;
    int sa_b = 0;

    qa = a/10;
    qb = b/10;

    ra = a%10;
    rb = b%10;
    
    if (ra == 1 && rb == 1) {
        sa_b = 0;
        carry = 1;
    } else if ((ra == 1 || rb == 1) && carry == 1) {
        sa_b = 0;
        carry = 1;
    } else if ((ra == 1 || rb == 1)){
        sa_b = 1;
        carry = 0;
    } else {
        sa_b = 0;
        carry = 0;
    }

    if (!qa && !qb) {
        bin_sum = carry * 10 * base_ten + bin_sum;
        printf("Binary sum is %d", bin_sum);
    } else {
        bin_sum = sa_b * base_ten + bin_sum;
        base_ten *= 10;
        bin_add(qa, qb, carry, base_ten, bin_sum);
    }
}
