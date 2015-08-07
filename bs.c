#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int *, int);

int main() {
    int array[] = {12, 78, 34, 56, 12, 98, 76, 24, 44, 40, 11};
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

    while (i < len) {
        key = array[i];
    }
}

