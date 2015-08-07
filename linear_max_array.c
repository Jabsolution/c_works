#include <stdio.h>
#include <stdlib.h>

int get_max_subarray_sum(int *, int);

int main() {
     int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

    int len = sizeof(a)/sizeof(int);
    int i = 0;
    int max_sum = 0;

    printf("len: %d", len);
    max_sum = get_max_subarray_sum(a, len);
    printf("MAX: %d", max_sum);
}

int get_max_subarray_sum(int *a, int len) {
    int max_array = 0;
    int sum = 0;
    int i = 0;

    for (i = 0; i <= len - 1; i++) {
        if (sum <= sum + a[i]) {
            if (max_array <= (sum + a[i])) {
                max_array = sum + a[i];
                printf("\n max_Array found so far: %d", max_array);
            } else if (max_array <= a[i]) {
                max_array = a[i];
                printf("\n Looks like biggest: %d", max_array);
                sum = 0; // reset sum
            } else {
                printf("\n resetting at :%d", a[i]);
                sum = 0;
            }
        }
        sum += a[i];
        printf("\n sum: %d", sum);
    }
    return max_array;
}

