#include <stdio.h>
#include <stdlib.h>

void arrange_groups(int *, int);
int main() {
    int arr[10] = {1, 1, 1, 1, 1, 1, 1, 4, 3, 2};
    int i = 0;

    printf("Before: \n"); 
    for(i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
   
    arrange_groups(arr, 3);
    printf("\nAfter: \n");
    for(i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void arrange_groups(int *arr, int threshold) {
    int slow_idx = 0;
    int fast_idx = 1;
    int swap_idx = 0;
    int m = 1;
    int tmp = 0;

    while (fast_idx < 10) {
        if (arr[slow_idx] == arr[fast_idx]) {
            ++m;
            if (m > threshold) {
                if (!swap_idx)
                    swap_idx = fast_idx; 
                m = 1;
            }
        } else {
            if (swap_idx) {
                tmp = arr[swap_idx];
                arr[swap_idx] = arr[fast_idx];
                arr[fast_idx] = tmp;
                // Start slow_idx and fast_idx at the swapped index
                slow_idx = swap_idx;
                fast_idx = slow_idx + 1;
                swap_idx = 0;
            }
            m = 1;
        }
        slow_idx++;
        fast_idx++;
    }
    if (swap_idx) {
        printf("Invalid string\n");
    }

}
