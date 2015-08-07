#include <stdio.h>
#include <stdlib.h>

void calling_function(int *ptr, int, int);

int main() {
    int func_array[2][5] = { {2, 3, 4, 5, 6}, {4, 34, 23, 43, 23} };
    int *p = NULL;
    p = &(func_array[0][0]);
    calling_function(p, 2, 5);
}

void calling_function(int *ptr, int row, int col) {
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d\n", *(ptr++));
        }
    }
}


