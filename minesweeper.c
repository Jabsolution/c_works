#include <stdio.h>
#include <stdlib.h>

int** print_mines(int, int);
int main() {
    int a = 0;
    int b = 0;
    int c = 0;
    int i = 0;
    int j = 0;
    while (c = getch() != EOF) {
        if (c < '1' || c > '9') {
            printf("Needs digits");
        }
    }
    scanf("%d %d", &a, &b);
    printf("%d %d", a, b);
    int **matrix = NULL;
    matrix = print_mines(a, b);
    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

int **print_mines(int a, int b) {
    int i = 0;
    int j = 0;
    int **mat = NULL;

    mat = (int **)malloc(a * sizeof(int *));

    for (i = 0; i < a; i++) {
        mat[i] = (int *)malloc(b * sizeof(int));
    }

    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            mat[i][j] = '.';
        }
    }

    printf("\n");

    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }
    mat[0][0] = '*';
    mat[2][2] = '*';
    return mat;
}

