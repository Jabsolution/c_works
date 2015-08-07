#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_mat(int *, int);
int test(unsigned int *, int);
void populate_array(unsigned int **t, int);

int main(int argc, char *argv[]) {
    int total = 0;
    int rows  = strtol(argv[1], NULL, 10);
    printf("ROWS: %d\n", rows);
    unsigned int *t = NULL;
    populate_array(&t, rows);
    total = test(t, rows);
    printf("Total: %d\n", total);
}

void populate_array(unsigned int **ret_array, int rows) {
    FILE *fp;
    int size = 0;
    int total_int = (rows * (rows + 1)) / 2;
    int i = 0;
    char *t = NULL;
    char *byte = malloc(sizeof(char) * 3);
    unsigned int *t_i = malloc(sizeof(unsigned int) * total_int);
    int idx = 0;

    fp = fopen("p067_triangle.txt", "r");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    t = malloc(sizeof(char) * size);

    printf("size: %d and total_int: %d", size, total_int);
    rewind(fp);

    fread(t, 1, size, fp);

    while(i <= size) {
        if (t[i] < '0' || t[i] > '9') {
            i++;
            continue;
        }
        // Copy two bytes to byte string
        strncpy(byte, &t[i], 2);
        byte[2] = '\0';
        t_i[idx] = strtol(byte, NULL, 10);
        idx++;
        i += 2;
    }

    idx = 0;
    while (idx < total_int) {
        printf("%d ", t_i[idx]);
        idx++;
    }


    *ret_array = t_i;
}

int test(unsigned int *t, int row) {
    int left_sum = 0;
    int right_sum = 0;
    int s_idx = ((row * (row + 1)) / 2) - 1;
    int num_ele = s_idx + 1;
    int middle = 0;
    int adj_idx = 0;
    int ele = 0;

    printf("\n");
    while (row > 0) {
        ele = row;
        while (ele > 0) {

            adj_idx = s_idx + row; 
            middle = adj_idx + 1;
        
            if (middle < num_ele) {
                left_sum = t[s_idx] + t[adj_idx];
                right_sum = t[s_idx] + t[middle];

                if (left_sum > right_sum) {
                    t[s_idx] = left_sum;
                } else {
                    t[s_idx] = right_sum;
                }
            }

            s_idx--;
            ele--;
        }
        printf("\n");

        row--;
    }
    return t[s_idx + 1];
}

void print_mat(int *t, int len) {
    int row = 0;
    int ele = 0;
    int s_idx = 0;

    while (row < len) {
        while (ele >= 0) {
            printf("%d ", t[s_idx]);
            s_idx++;
            ele--;
        }
        printf("\n");
        ele = row + 1;
        row++;
    }

}

