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

void max_subarray(int *array, int len, int *left_index, int *right_index, int *sum) {
    int i = 0;
    int j = 0;
    int lo = 0;
    int hi = 0;
    int max = 0;
    int local_sum = 0;

    for (i = 0; i < len; i++) {
        local_sum = 0;
        for (j = i; j < len; j++) {
            local_sum += array[j];
            if (max < local_sum) {
                hi = j;
                lo = i;
                max = local_sum;
            }
        }
    }

    *left_index = lo;
    *right_index = hi;
    *sum = max;
}
