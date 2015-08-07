#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *, int);

int main() {
    int array[] = {12, 78, 34, 56, 36, 98, 76, 24, 44, 40, 11, 13};
    int len = sizeof(array) / sizeof(int);
    int i = 0;

    insertion_sort(array, len);

    for (i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }
    
}

void insertion_sort(int *array, int len) {
    int i = 1;
    int j = 0;
    int lo = 0;
    int hi = 0;
    int mid = 0;
    int key = 0;
    int k = 0;

    while (i < len) {
        key = array[i];
        j = i - 1;
        hi = j;
        lo = 0;

        while (lo <= hi) {
            mid = (lo + hi) / 2;

            if (key < array[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        // At some point of time lo will cross high
        k = lo;

        while (j >= k) {
            array[j + 1] = array[j];
            j -= 1;
        }
        array[k] = key;

        i += 1;
    }
}

