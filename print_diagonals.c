#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[4][4] = {
        {8, 2, 22, 97},
        {49, 49, 99, 40},
        {81, 49, 31, 73},
        {52, 70, 95, 23},
    };
    int i = 0;
    int j = 0;
    int k = 0;
    int tmp = 0;
    int l = 1;

    for (i = 1; i < 4; i++) {
        k = i;
        for (j = 0; j <= i; j++) {
            printf("%d ", a[k--][j]);
        }
        printf("\n");
    }

    for (j = 1; j < 3; j++) {
        k = j;
        for (i = 3; i >= j; i--) {
            printf("%d ", a[i][k++]);
        } 
        printf("\n");
    }

}
