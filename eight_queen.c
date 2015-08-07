#include <stdio.h>
#include <stdlib.h>

int print_solutions(int **, int, int, int, int, int sol_no);
int **get_matrix(int, int);
int is_safe(int **, int, int, int, int);

int main() {
    int row = 8;
    int col = 8;
    int i = 0;
    int j = 0;
    int **mat = NULL;
    
    mat = get_matrix(row, col);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            mat[i][j] = 0;
        }
    }
    print_solutions(mat, row, col, 0, 8, 0);
}

int **get_matrix(int a, int b) {
    int i = 0;
    int j = 0;
    int **mat = NULL;

    mat = (int **)malloc(a * sizeof(int *));

    for (i = 0; i < a; i++) {
        mat[i] = (int *)malloc(b * sizeof(int));
    }
    return mat;
}

int print_solutions(int **mat, int row, int col, int next_row, int queens, int sol_no) {
    int i = 0;
    int j = 0;

    if (!queens && (next_row == row)) {
        sol_no++;
        printf("Solution: %d\n", sol_no);
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (mat[i][j] == 'X') 
                    printf("%c", mat[i][j]);
                else
                    printf("%d", mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return sol_no;
    }

    for(i = next_row; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (is_safe(mat, row, col, i, j)) {
                mat[i][j] = 'X';
                sol_no = print_solutions(mat, row, col, i + 1, queens - 1, sol_no);
                mat[i][j] = 0;
            }
        }
        break;
    }
    return sol_no;
}

int is_safe(int **mat, int row, int col, int c_row, int c_col) {
    int i = 0;
    int j = 0;

    /*
     * Left diagonal
     *     *
     *    /
     *   /
     *  * 
     */
    for(i = c_row, j = c_col; i >= 0 && j >= 0; i--, j--) {
        if (mat[i][j] == 'X') {
            return 0;
        }
    }


    /*
     * Down column
     *     *
     *     |
     *     |
     *     *
     */
    for (i = c_row, j = c_col; i >= 0; i--) {
        if (mat[i][j] == 'X') {
            return 0;
        }
    }

    /*
     * Right diagonal
     *      *
     *       \
     *        \
     *         *
     */
    for (i = c_row, j = c_col; i >= 0 && j < col; i--, j++) {
        if (mat[i][j] == 'X') {
            return 0;
        }
    }
    return 1;
}

