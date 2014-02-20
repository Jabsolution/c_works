#include <stdio.h>
#include <stdlib.h>

void swap(int *, int, int);
void print_subset(int *, int, int, int, int, int *);
int main() {
    int arr[] = {3, 6, 5, 4};
    int n = 4;
    int k = 3;
    int buf_str[3] = {};
    print_subset(arr, 0, n, k, 0, buf_str);
}

void swap(int *a, int j, int i) {
    int tmp = 0;
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void print_subset(int *a, int j, int n, int k, int idx, int *buf_str) {
     int i = 0;
     int m = 0;
     int l = 0;

     if (k == 1) {
         for (l = j; l < n; l++) {
             buf_str[idx] = a[l];
             for (m = 0; m <= idx; m++) {
                printf("%d ", buf_str[m]);
             }
             printf("\n");
         }
         return;
     }
     for (i = j; i < n; i++) {
        swap(a, j, i);
        buf_str[idx++] = a[j];
        print_subset(a, j + 1, n, k - 1, idx, buf_str);
        swap(a, j, i);
        --idx;
     }  
}


