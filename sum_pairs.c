#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_pairs(int *, int, int);
int main() {
    int a[] = {2, 5, 3, 7, 9, 8, 4};
    int len = sizeof(a) / sizeof(int);
    int i = 0;
    int sum_hash[11] = {0};
    int sum = 11;
    int next_pair = 0;

    find_pairs(a, len, sum);

}
void find_pairs(int *a, int len, int sum) {
    int sum_hash[sum];
    int i = 0;
    int next_pair = 0;

    memset(sum_hash, 0, sizeof(sum_hash));

    for (i = 0; i < len; i++) {
        next_pair = 11 - a[i];
        if (sum_hash[next_pair]) {
            printf("%d %d\n", a[i], next_pair);
        } else {
            sum_hash[a[i]] = 1;
        }
    }    
}

