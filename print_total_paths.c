#include <stdio.h>
#include <stdlib.h>

/* This program prints all the possible paths from length 1 to m * n in m * n matrix.
 * It also prints the total number of possible paths.
 *
 * We need to figure out a way to calculate the total number of paths without going through all
 * of them.
 */
typedef struct _vertex {
    char val;
    int color;
} vertex;

int matrix[16][16]={{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //a
                    {1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //b
                    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //c
                    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //d
                    {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, //e
                    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0}, //f
                    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0}, //g
                    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0}, //h
                    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, //i
                    {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //j
                    {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, //k
                    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1}, //l
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, //m
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //n
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1}, //o
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1}};//p


int row = 16;
int col = 16;
unsigned int total = 0;
void dfs(vertex *, int, char *, int);
void reset_vertex_color(vertex *, int);

int main() {
    int len = row * col;
    int i = 0;
    int k = 0;
    int j = 0;
    char str[17];
    vertex *v = malloc(sizeof(vertex) * col);


    reset_vertex_color(v, 0);
    /* We traverse all paths from all vertices */
    for (i = 0; i < col; i++) {
        if (!v[i].color) {
            dfs(v, i, str, 0);
        }
        // Reset all vertices for the next round
        reset_vertex_color(v, 0);
    }
    //The number of total possible paths
    printf("\n Total paths: %d\n", total);
}

void reset_vertex_color(vertex *v, int v_idx) {
    int i = 0;
    for (i = v_idx; i < col; i++) {
        v[i].val = 'a' + i;
        v[i].color = 0;
    }
}

void dfs(vertex *v, int i, char *str, int str_idx) {
    int j = 0;
    int k = 0;
    int l = 0;

    v[i].color = 1;
    str[str_idx++] = v[i].val;
    str[str_idx] = '\0';
    printf("%s ", str);

    total++;

    for (k = 0; k < row; k++) {
        if (!v[k].color && matrix[i][k]) {
            dfs(v, k, str, str_idx);
            // Once visited, reset the color of the vertex
            v[k].color = 0;
        }
    }

}

