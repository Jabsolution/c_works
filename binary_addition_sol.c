#include <stdio.h>
#include <stdlib.h>

void bin_add(int, int, int, int, int);

int main() {
    int a = 1011;
    int b =  110;
    bin_add(a, b, 0, 1, 0);
}

void bin_add(int a, int b, int cremote, int base_ten, int bin_sum) {
    int qa = 0;
    int qb = 0;
    int ra = 0;
    int rb = 0;
    int result = 0;
    int clocal = 0;

    qa = a/10;
    qb = b/10;

    if (!a && !b) {
        if (cremote)
            bin_sum = cremote * base_ten + bin_sum;
        printf("Binary sum is %d", bin_sum);
        return;
    }

    ra = a%10;
    rb = b%10;

    clocal = ra & rb;
    result = (ra ^ rb) ^ cremote;
    if (result == 0 && (ra || rb))
        clocal = 1;

    bin_sum = result * base_ten + bin_sum;
    base_ten *= 10;
    printf("clocal is %d\n", clocal);
    bin_add(qa, qb, clocal, base_ten, bin_sum);
}
