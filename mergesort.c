#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void divide(int *, int, int);

int main() {
    int array[] = {98, 34, 5, 87, 34, 15, 10, 12, 89, 33, 8, 6, 1};
    int lo = 0;
    int hi = sizeof(array) / sizeof(int);
    int i = 0;

    divide(array, lo, hi - 1);

    for(i = 0; i < hi; i++) {
        printf("%d ", array[i]);
    }
}

void divide(int *array, int lo, int hi) {
    int mid;
    int *left = NULL;
    int *right = NULL;
    int i = 0;
    int j = 0;

    if (lo == hi)
        return;

    mid = (lo + hi) / 2;

    // Divide
    divide(array, lo, mid);
    divide(array, mid + 1, hi);

    // Get total 
    i = (mid - lo) + 1;
    j = (hi - mid);
    left = malloc(sizeof(int) * i);
    right = malloc(sizeof(int) * j);
    memcpy(left, &array[lo], sizeof(int) * i);
    memcpy(right, &array[mid + 1], sizeof(int) * j);

    // Length to index
    i -= 1;
    j -= 1;
    
    // Merge or Conquer
    while (lo <= hi) {
        if (i >= 0 && j >= 0) {
            if (left[i] < right[j]) {
                array[hi] = right[j];
                j -= 1;
            } else {
                array[hi] = left[i];
                i -= 1;
            }
        } else {
            if (j >= 0) {
                array[hi] = right[j];
                j -= 1;
            } else {
                array[hi] = left[i];
                i -= 1;
            }
        }
        hi -= 1;
    } 
}

