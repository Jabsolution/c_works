#include <stdio.h>
#include <stdlib.h>

int partition(int *, int, int);
void quicksort(int *, int, int);
void exchange(int *, int *);

int main() {
    int val[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    int len = sizeof(val)/sizeof(int);
    int q;
    int r;
    int i = 0;

    quicksort(val, 0, len - 1);
    for (i = 0; i < len - 1; i++) {
        printf("%d ", val[i]);
    }
}

void quicksort(int *val, int p, int r) {
    int q = 0;

    if (p < r) {
        q = partition(val, p, r);
        quicksort(val, p, q - 1);
        quicksort(val, q + 1, r);
    }
}

int partition(int *val, int p, int r) {
    int x = 0;
    int i = 0;
    int j = 0;

    i = p - 1;
    x = val[r]; // the pivot
    for (j = p; j <= r - 1; j++) {
        if (val[j] <= x) {
            i = i + 1;
            exchange(&val[i], &val[j]);
        }
    }
    exchange(&val[i + 1], &val[r]);
    return i + 1;
}

void exchange(int *s, int *d) {
    if (s == d)
        return;
    *s = *s + *d;
    *d = *s - *d;
    *s = *s - *d;
}
