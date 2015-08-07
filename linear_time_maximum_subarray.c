#include <stdio.h>
#include <stdlib.h>

void max_subarray(int *, int, int *, int *, int *);
int main() {
    int array[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int len = sizeof(array) / sizeof(int);
    int left_index = 0;
    int right_index = 0;
    int sum = 0;

    max_subarray(array, len, &left_index, &right_index, &sum);

    printf("ST_I: %d END_I: %d SUM: %d", left_index, right_index, sum); 
}

void max_subarray(int *a, int len, int *left_index, int *right_index, int *sum) {
    int i = 0;
    int j = 0;
    int lo = 0;
    int hi = 0;
    int max = 0;
    int local_sum = 0;
    int temp_start = 0;

    max = a[0];
    for (i = 1; i < len; i++) {
        // Maximum subarray of a[1 .. j + 1] is
        // either a[1 .. j] or a[1 .. j + 1]
        if (a[i] + a[i - 1] > max) {
            hi = i;
            max = a[i] + a[i - 1];
            a[i] = a[i] + a[i - 1];

            if (i - 1 == temp_start) {
                lo = temp_start;
            }
        } else if (a[i] > max) {
            lo = i; 
            hi = i;
            max = a[i];
        } else {
            if (a[i] + a[i - 1] > a[i]) {
                a[i] = a[i] + a[i - 1];
            } else {
                // Possible starting point
                temp_start = i;
            }
        }
    }

    *left_index = lo;
    *right_index = hi;
    *sum = max;
}
