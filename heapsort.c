#include <stdio.h>
#include <stdlib.h>

#define LEFT(x) 2 * x + 1
#define RIGHT(x) 2 * x + 2

void buildHeap(int *, int);
void heapify(int *, int, int);
void heapSort(int *, int);
void swap(int *, int, int);

void swap(int *a, int src, int dest) {
    int tmp = 0;

    tmp = a[dest];
    a[dest] = a[src];
    a[src] = tmp;
}

int main() {
    int a[] = {45, 3, 14, 7, 5, 90, 7, 12, 10, 4, 19};
    int size = sizeof(a) / sizeof(int);
    int i = 0;
    
    buildHeap(a, size);
    heapSort(a, size);
    for (i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
}

void heapSort(int *a, int size) {
    int i = 0;

    // Swap a[0] with a[i]
    for (i = size - 1; i >= 0; i--) {
        swap(a, 0, i);
        heapify(a, 0, i);
    }
}

void buildHeap(int *a, int size) {
    int i = 0;

    for (i = (size / 2); i >= 0; i--) {
        heapify(a, i, size);
    }
}

void heapify(int *a, int parent, int size) {
    int left = 0;
    int right = 0;
    int largest = 0;

    left = LEFT(parent);
    right = RIGHT(parent);


    if (left < size && a[left] > a[parent]) {
        largest = left;
    } else {
        largest = parent;
    }

    if (right < size && a[largest] < a[right]) {
        largest = right;
    }

    if (largest != parent) {
        swap(a, largest, parent);
        heapify(a, largest, size);
    }
}


