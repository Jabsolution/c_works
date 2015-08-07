#include <stdio.h>
#include <stdlib.h>

int get_max_subarray_sum(int *, int, int);
int get_crossing_sum(int *, int, int, int);

int main() {
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

    int len = sizeof(a)/sizeof(int);
    int i = 0;
    int max_sum = 0;

    printf("len: %d", len);
    max_sum = get_max_subarray_sum(a, 0, len - 1);
    printf("MAX: %d", max_sum);
}

int get_max_subarray_sum (int *a, int lo, int hi) {
    int mid = 0;
    int left_sum = 0;
    int right_sum = 0;
    int cross_sum = 0;

    if (lo == hi)
        return (a[lo]);

    mid = (lo + hi)/2;

    left_sum = get_max_subarray_sum(a, lo, mid);
    right_sum = get_max_subarray_sum(a, mid + 1, hi);
    cross_sum = get_crossing_sum(a, lo, mid, hi);

    if (left_sum >= right_sum && left_sum >= cross_sum)
        return left_sum;
    else if (right_sum >= cross_sum)
        return right_sum;
    else
        return cross_sum;
}

int get_crossing_sum(int *a, int lo, int mid, int hi) {
    int left_sum = 0;
    int right_sum = 0;
    int sum = 0;
    int i = 0;

    for (i = mid; i >= lo; i--) {
        sum = sum + a[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }

    sum = 0;
    for (i = mid + 1; i <= hi; i++) {
        sum = sum + a[i];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }
    return (left_sum + right_sum);
}
