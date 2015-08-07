#include <stdio.h>
#include <stdlib.h>

typedef struct _vertex {
    int val;
    int color;
} vertex;

vertex ** form_matrix(int, int);
void print_all_paths(char *, vertex **, int, int, int);

int m = 3;
int n = 3;

int main() {
    int j = 0;
    int k = 0;
    vertex **matrix = NULL;
    char *str = malloc(sizeof(char) * 10);
    matrix = form_matrix(m, n);
    for (j = 0; j < m; j++) {
        for (k = 0; k < n; k++) {
            matrix[j][k].color = 1;
            printf("New cell: %d", matrix[j][k].val );
            print_all_paths(str, matrix, j, k, 0);
            matrix[j][k].color = 0;
        }
        printf("\n\n");
    }
}

vertex** form_matrix(int m, int n) {
    vertex **matrix;
    int offset = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    matrix = malloc(sizeof(vertex *) * m);

    for (i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(vertex) * n);
    }


    i = 0;
    for (j = 0; j < m; j++) {
        for (k = 0; k < n; k++) {
            matrix[j][k].val = (i * m) + offset;
            matrix[j][k].color = 0;
            offset++;
        }
        i++;
        offset = 0;
    }

    return matrix;
}

void print_all_paths(char *str, vertex **matrix, int i, int j, int str_idx) {
    
    if (i < n && j < m && i >= 0 && j >= 0) {
        str[str_idx] = matrix[i][j].val;
        str[str_idx + 1] = '\0';
        printf("%s", str);
        matrix[i][j].color = 1;
    } else {
        return;
    }
    // Right
    if (j + 1 < n && !matrix[i][j + 1].color) {
        print_all_paths(str, matrix, i, j + 1, str_idx++);
    }
    // Left
    if (j - 1 >= 0 && !matrix[i][j - 1].color) {
        print_all_paths(str, matrix, i, j - 1, str_idx++);
    }
    // Up
    if (i - 1 >= 0 && !matrix[i - 1][j].color) {
        print_all_paths(str, matrix, i - 1, j, str_idx++);
    }
    // Down
    if (i + 1 < n && !matrix[i + 1][j].color) {
        print_all_paths(str, matrix, i + 1, j, str_idx++);
    }
 
    // Top Right Corner
    if (i - 1 >= 0 && j + 1 < m && !matrix[i - 1][j + 1].color) {
        print_all_paths(str, matrix, i - 1, j + 1, str_idx++);
    }

    // Bottom Right Corner
    if (i + 1 < n && j + 1 < m && !matrix[i + 1][j + 1].color) {
        print_all_paths(str, matrix, i + 1, j + 1, str_idx++);
    }

    // Bottom Left Corner
    if (i + 1 < n && j - 1 >= 0 && !matrix[i + 1][j - 1].color) {
        print_all_paths(str, matrix, i + 1, j - 1, str_idx++);
    }

    // Top Left Corner
    if (i - 1 >= 0 && j - 1 >= 0 && !matrix[i - 1][j - 1].color) {
        print_all_paths(str, matrix, i - 1, j - 1, str_idx++);
    }
    matrix[i][j].color = 0;

}
