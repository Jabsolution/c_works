#include <stdio.h>
#include <stdlib.h>

typedef struct _matrix {
    int val;
    int flipped;
} matrix;

void print_matrix(matrix (*)[4], int, int);
int main() {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int M = 4;
    int N = 4;
    matrix m[4][4] = {
        {{1, 0}, {1, 0}, {1, 0}, {1, 0}},
        {{1, 0}, {0, 0}, {1, 0}, {1, 0}},
        {{1, 0}, {1, 0}, {1, 0}, {1, 0}},
        {{1, 0}, {1, 0}, {1, 0}, {1, 0}}
    };

    print_matrix(m, M, N);
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            if (!m[i][j].val && !m[i][j].flipped) {
                for (k = 1; k < M; k++) {
                    if (i + k <= M - 1) {
                        if (m[i + k][j].val && !m[i + k][j].flipped) {
                            m[i + k][j].val = 0;
                            m[i + k][j].flipped = 2;
                        }
                    }
                    if (i >= k) {
                        if (m[i - k][j].val && !m[i - k][j].flipped) {
                            m[i - k][j].val = 0;
                            m[i - k][j].flipped = 1;
                        }
                    }
                }
                print_matrix(m, M, N);
                for(l = 1; l < M; l++){
                    if (j + l <= M - 1) {
                        if (m[i][j + l].val && !m[i][j + l].flipped) {
                            m[i][j + l].val = 0;
                            m[i][j + l].flipped = 1;
                        }
                    }
                    if (j >= l) {
                        if (m[i][j - l].val && !m[i][j - l].flipped) {
                            m[i][j - l].val = 0;
                            m[i][j - l].flipped = 1;
                        }
                    }
                }
            }
        }
    }
    print_matrix(m, M, N); 
}

void print_matrix(matrix (*m)[4], int M, int N) {
    int i = 0;
    int j = 0;
    for(i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d", m[i][j].val);
        }
        printf("\n");
    }
    printf("\n");
}
