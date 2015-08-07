#include <stdio.h>
#include <stdlib.h>

void maximum_crossing_arr(int *, int, int, int *, int *, int *);
void max_subarray(int *, int, int, int *, int *, int *);
int main() {
    int array[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int lo = 0;
    int hi = sizeof(array) / sizeof(int) - 1;
    int left_index = 0;
    int right_index = 0;
    int sum = 0;

    max_subarray(array, lo, hi, &left_index, &right_index, &sum);

    printf("ST_I: %d END_I: %d SUM: %d", left_index, right_index, sum); 
}

void max_subarray(int *array, int lo, int hi, int *left_index, int *right_index, int *sum) {
    int left_sum = 0;
    int right_sum = 0;
    int crossing_sum = 0;
    int left_sindex = 0;
    int left_eindex = 0;
    int right_sindex = 0;
    int right_eindex = 0;
    int crossing_s = 0;
    int crossing_e = 0;
    int mid = 0;
    if (lo == hi) {
        *left_index = lo;
        *right_index = hi;
        *sum = array[lo];
    } else {
        mid = (lo + hi) / 2;
        max_subarray(array, lo, mid, &left_sindex, &left_eindex, &left_sum);
        max_subarray(array, mid + 1, hi, &right_sindex, &right_eindex, &right_sum);
        maximum_crossing_arr(array, lo, hi, &crossing_s, &crossing_e, &crossing_sum);

        if (left_sum <= right_sum && right_sum >= crossing_sum) {
            *left_index = right_sindex;
            *right_index = right_eindex;
            *sum = right_sum;
        } else if (left_sum >= crossing_sum) {
            *left_index = left_sindex;
            *right_index = left_eindex;
            *sum = left_sum;
        } else {
            *left_index = crossing_s;
            *right_index = crossing_e;
            *sum = crossing_sum;
        }
    }
}

void maximum_crossing_arr(int *array, int lo, int hi, int *l_index, int *r_index, 
        int *sum) {
    int mid = (lo + hi) / 2;
    int i = 0;
    int left_sum = 0;
    int right_sum = 0
    int local_sum = 0;

    // Initial conditions for the sums and indices
    left_sum = array[mid];
    *l_index = mid;
    right_sum = array[mid + 1];
    *r_index = mid + 1;

    i = mid;
    while (i >= lo) {
        local_sum += array[i];
        if (left_sum < local_sum) {
            *l_index = i;
            left_sum = local_sum;
        }
        i -= 1;
    }

    i = mid + 1;
    local_sum = 0;
    while (i <= hi) {
        local_sum += array[i];
        if (right_sum < local_sum) {
            *r_index = i;
            right_sum = local_sum;
        }
        i += 1;
    }
    *sum = right_sum + left_sum;
}
