#include <stdlib.h>
#include <stdio.h>
#define M 4

void print_diagonals(int (*a)[], int, int, int);

int main() {
    int a[4][4] = {
        {8, 2, 22, 97},
        {49, 49, 99, 40},
        {81, 49, 31, 73},
        {52, 70, 95, 23},
    };
    print_diagonals(a, 1, 5, 0);
    print_diagonals(a, 1, 5, 1);
}

void print_diagonals(int (*a)[4], int lo, int hi, int dir) {
    int mid = 0;
    mid = (lo + hi) / 2;
    int i = 0;
    int k = 0;
    int j = 0;

    if (lo == hi) {
        if (lo >= M && hi >= M) {
            lo = (lo - M) + 1;
            hi = (hi - M) + 1;
            if (!dir) {
                k = lo;
                for (i = M - 1; i >= lo; i--) {
                    printf("%d ", a[i][k++]);
                }
                printf("\n");
            } else {
                k = (M - 1) - lo ;
                for (i = M - 1; i >= lo; i--) {
                    printf("%d ", a[i][k--]);
                }
                printf("\n");
            }
            return;
        } else {
            if (!dir) {
                k = lo;
                for (j = 0; j <= lo; j++) {
                    printf("%d ", a[k--][j]);
                }
                printf("\n");
            } else {
                k = lo;
                for (j = M - 1; k >= 0; j--) {
                    printf("%d ", a[k--][j]);
                }
                printf("\n");
            }
            return;
        }
    }
    print_diagonals(a, lo, mid, dir);
    print_diagonals(a, mid + 1, hi, dir);

}

